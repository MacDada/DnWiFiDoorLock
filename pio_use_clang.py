# Switches PlatformIO to be using Clang instead of the default toolchain (most likely GCC).
# Activate it with `extra_scripts = post:pio_use_clang.py` in `platformio.ini` config.

Import("env")
Import("projenv")

verbose = False
veryVerbose = False

if veryVerbose:
    print(env.Dump())
    print(projenv.Dump())

print("\nReplacing the default toolchain with Clang…\n")

for theEnvName, theEnv in {"env": env, "projenv": projenv}.items():
    if verbose or veryVerbose:
        print(f"Default CC ({theEnvName}): {theEnv.get('CC')}")
        print(f"Default CXX ({theEnvName}): {theEnv.get('CXX')}")

    # Preserve C and C++ build flags
    cflagsBackup = theEnv.get("CFLAGS", [])
    cxxflagsBackup = theEnv.get("CXXFLAGS", [])

    theEnv.Tool("clang")
    theEnv.Tool("clang++")

    # Restore C/C++ build flags as they were overridden by env.Tool
    theEnv.Append(
        CFLAGS=cflagsBackup,
        CXXFLAGS=cxxflagsBackup
    )

    if verbose or veryVerbose:
        print(f"\nReplaced CC ({theEnvName}): {theEnv.get('CC')}")
        print(f"Replaced CXX ({theEnvName}): {theEnv.get('CXX')}\n")

if veryVerbose:
    print(env.Dump())
    print(projenv.Dump())
