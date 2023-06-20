from SCons.Script.SConscript import SConsEnvironment
from pathlib import Path
from platformio.compat import MISSING
from platformio.platform.base import PlatformBase
from platformio.project.config import ProjectConfigBase
from platformio.project.config import ProjectOptions
from platformio.project.options import ConfigEnvOption
from typing import Callable
from utils import partition


class PackageNotAvailableError(ValueError):
    pass


class Helper:
    def __init__(self, script_globals: dict):
        """
        :param script_globals: Pass in `globals()` and let the magic do its job…
        """

        # global env
        self.default_env: SConsEnvironment = script_globals['DefaultEnvironment']()

        # project env
        self.default_env.Import('projenv')
        self.projenv: SConsEnvironment = script_globals['projenv']

        # current working env
        self.default_env.Import('env')
        self.env: SConsEnvironment = script_globals['env']

        self.envs = [
            self.default_env,
            self.projenv,
            self.env,
        ]

    def register_custom_config_option(
        self,
        name: str,
        description: str,
        default=None,
        multiple: bool = False,
        type: Callable = str,
        processor: Callable = None
    ) -> None:
        """
        https://docs.platformio.org/en/latest/scripting/examples/platformio_ini_custom_options.html
        https://community.platformio.org/t/custom-platformio-ini-options-as-list-str-not-str/34380/6
        """

        option = ConfigEnvOption(
            group='custom',
            name=name,
            description=description,
            type=type,
            multiple=multiple,
            default=default,
            validate=processor,
        )
        ProjectOptions['%s.%s' % (option.scope, option.name)] = option

    def get_config_value_as_list(self, name: str) -> list[str]:
        """
        https://docs.platformio.org/en/latest/scripting/examples/platformio_ini_custom_options.html
        https://community.platformio.org/t/custom-platformio-ini-options-as-list-str-not-str/34380/2
        """

        return self.get_project_config().parse_multi_values(
            self.get_config_value(name)
        )

    def get_config_value(self, name: str, default=MISSING):
        """
        https://docs.platformio.org/en/latest/scripting/examples/platformio_ini_custom_options.html
        """

        return self.env.GetProjectOption(name, default=default)

    def get_project_config(self) -> ProjectConfigBase:
        return self.env.GetProjectConfig()

    def get_platform(self) -> PlatformBase:
        """
        The platform is the same for all the envs.
        """

        return self.env.PioPlatform()

    def list_available_packages(self) -> list[str]:
        return [
            package.metadata.name
            for package
            in self.get_platform().get_installed_packages()
        ]

    def list_used_packages(self) -> list[str]:
        return [
            package['name']
            for package
            in self.get_platform().dump_used_packages()
        ]

    def mark_packages_as_system(self, packages: list[str]) -> None:
        """
        See :meth:`~pio_extra_script_helper.Helper.mark_package_as_system`
        """

        for package in packages:
            self.mark_package_as_system(package)

    def mark_package_as_system(self, package: str) -> None:
        """
        Adds `-isystem` flag to the specified package.

        As the result, most of the warnings – for this package – will be silenced.

        https://gcc.gnu.org/onlinedocs/cpp/System-Headers.html
        https://gcc.gnu.org/onlinedocs/gcc/Directory-Options.html#Options-for-Directory-Search

        Inspiration:
        https://community.platformio.org/t/silence-warnings-for-dependencies-external-libraries/33387/8
        """

        try:
            package_to_mark_as_system_path: Path = self.get_path_of_package(package)
        except PackageNotAvailableError as e:
            raise PackageNotAvailableError(
                f'Could not mark the package "{package}" as system – it is not available. '
                f'See :meth:`~pio_extra_script_helper.Helper.list_available_packages`'
            ) from e

        for env in self.envs:
            system_paths, not_system_paths = partition(
                lambda path_from_env: package_to_mark_as_system_path in Path(path_from_env).parents,
                env['CPPPATH']
            )

            # `CPPPATH` – paths containing both `C` and `C++` files
            # https://scons.org/doc/4.5.2/HTML/scons-user/apa.html#cv-CPPPATH
            env.Replace(CPPPATH=not_system_paths)

            # `CCFLAGS` – options for both C and C++ compilers
            # https://scons.org/doc/4.5.2/HTML/scons-user/apa.html#cv-CCFLAGS
            #
            # Not using `CXXFLAGS` as the `CPPPATH` apparently contains files for both `C` and `C++`:
            # https://community.platformio.org/t/silence-warnings-for-dependencies-external-libraries/33387/11
            env.Append(CCFLAGS=[
                ('-isystem', system_path)
                for system_path
                in system_paths
            ])

    def get_path_of_package(self, package: str) -> Path:
        platform: PlatformBase = self.get_platform()

        try:
            package_dir: str = platform.get_package_dir(package)
        except KeyError as e:
            raise PackageNotAvailableError(
                f'Could not get path of the package "{package}" – it is not available. '
                f'See :meth:`~pio_extra_script_helper.Helper.list_available_packages`'
            ) from e

        return Path(package_dir)
