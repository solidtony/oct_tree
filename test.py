from build import build_project
from helper import parse_args
from helper import run


def test_project(clean=False, config="Release", generator="Ninja Multi-Config"):
    conan_preset = f"conan-{config.lower()}"
    build_project(clean=clean, config=config, generator=generator)

    run(f"ctest --preset {conan_preset}")

if __name__ == "__main__":
    args = parse_args()

    test_project(
        clean=args.clean,
        config=args.config,
        generator=args.cmake_generator
    )
