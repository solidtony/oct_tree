from argparse import ArgumentParser
import os
import platform
import re
import subprocess


def run(cmd, error=False):
    process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    out, err = process.communicate()
    out = out.decode("utf-8")
    err = err.decode("utf-8")
    ret = process.returncode

    output = err + out
    print("Running: {}".format(cmd))
    print("-------- OUTPUT --------")
    print(output)
    print("-------- END OUTPUT --------")
    if ret != 0 and not error:
        raise Exception("Failed cmd: {}\n{}".format(cmd, output))
    if ret == 0 and error:
        raise Exception(
            "Cmd succeded (failure expected): {}\n{}".format(cmd, output))
    return output

def parse_args():
    parser = ArgumentParser()
    parser.add_argument(
        "-c",
        "--config",
        required=False,
        type=str,
        default="Release"
    )
    parser.add_argument(
        "-g",
        "--cmake-generator",
        required=False,
        type=str,
        default="Ninja Multi-Config"
    )
    parser.add_argument(
        "--clean",
        action="store_true"
    )

    return parser.parse_args()

def activate_venv():
    extension = 'bat' if platform.system() == "Windows" else "sh"
    cmd = 'call' if platform.system() == "Windows" else "source"
    script_path = os.path.abspath(os.path.join("build", "generators", f"conanbuild.{extension}"))
    run(f'{cmd} {script_path}')

def deactivate_venv():
    extension = 'bat' if platform.system() == "Windows" else "sh"
    cmd = 'call' if platform.system() == "Windows" else "source"
    script_path = os.path.abspath(os.path.join(".", "build", "generators", f"deactivate_conanbuild.{extension}"))
    run(f'{cmd} {script_path}')

def list_config_presets():
    if os.path.exists(os.path.join(".", "CMakeUserPresets.json")):
        output = run('cmake --list-presets')
        return re.findall(r'"(conan-.*?)"', output)
    return []

def list_build_presets():
    if os.path.exists(os.path.join(".", "CMakeUserPresets.json")):
        output = run('cmake --build --list-presets')
        return re.findall(r'"(conan-.*?)"', output)
    return []

def list_test_presets():
    if os.path.exists(os.path.join(".", "CMakeUserPresets.json")):
        output = run('ctest --list-presets')
        return re.findall(r'"(conan-.*?)"', output)
    return []
