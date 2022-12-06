#!/bin/bash
#
# Runs test(s) on file changes.
#
# Requires `fswatch`:
# https://github.com/emcrisostomo/fswatch
#
# Pass path to test dir as the first argument.
# For CLion's External Tools you can use `$FileRelativeDir$` macro var.
#
# Env is decided automatically from first dir after test root dir.
#
# Example usage:
#   * `./tdd.sh "test/native/*"`
#   * `./tdd.sh "test/native/Foo/test_foo/"`
#
# Thanks to `jcw` for inspiration:
# https://community.platformio.org/t/a-new-pio-tdd-workflow/21431

# without it colors don't work in CLion's output window
export PLATFORMIO_FORCE_ANSI=true

# first argument without test dir name
test_filter=${1#"test/"}
test_filter=${test_filter#"/test/"}

if [ -n "${test_filter}" ]
then
  test_filter_arg=" --filter=${test_filter}"
else
  test_filter_arg=""
fi

# extract the env from the first dir
test_env=$(echo "${test_filter}" | cut -d "/" -f 1)

if [ -n "${test_env}" ]
then
  test_env_arg=" -e ${test_env}"
else
  test_env_arg=""
fi

test_command="pio test${test_env_arg}${test_filter_arg}"

watch_dirs="config lib src test"

font_escape="\033["
font_reset="${font_escape}0m"

font_regular_blue="${font_escape}0;34m"
font_bold_blue="${font_escape}1;34m"
font_light_gray="${font_escape}0;37m"
font_italic="${font_escape}3m"

script_name=$(basename "${0}")

waiting_message="
${font_bold_blue}\
---
${script_name}: \
waiting for changes to run...
  \`\
${font_regular_blue}\
${font_italic}\
${test_command}\
${font_bold_blue}\`
---\
${font_reset}\
"

running_message="
${font_bold_blue}\
---
${script_name}: \
running...
  \`\
${font_regular_blue}\
${font_italic}\
${test_command}\
${font_reset}\
${font_bold_blue}\
\`
---\
${font_reset}
"

echo -e "${running_message}"
$test_command
echo -e "${waiting_message}"

is_not_temporary_file () {
  # checking the last char of the first argument
  [[ "${1: -1}" != "~" ]]
}

fswatch --latency 0.1 --recursive ${watch_dirs} |
  while read -r changed_file; do
    if is_not_temporary_file "${changed_file}"; then
      echo -e "\n\n${font_light_gray}File changed: \`${changed_file}\`${font_reset}"
      echo -e "${running_message}"
      $test_command
      echo -e "${waiting_message}"
    fi
  done
