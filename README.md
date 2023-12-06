<br/>
<p align="center">
  <h3 align="center">Pyro</h3>

  <p align="center">
    An experimental OS
    <br/>
    <br/>
    <a href="https://github.com/My-Bad-2/Pyro/issues">Report Bug</a>
    .
    <a href="https://github.com/My-Bad-2/Pyro/issues">Request Feature</a>
  </p>
</p>

![Contributors](https://img.shields.io/github/contributors/My-Bad-2/Pyro?color=dark-green) ![Issues](https://img.shields.io/github/issues/My-Bad-2/Pyro) ![License](https://img.shields.io/github/license/My-Bad-2/Pyro) 

## Table Of Contents

- [Table Of Contents](#table-of-contents)
- [About The Project](#about-the-project)
- [Built With](#built-with)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
  - [Creating A Pull Request](#creating-a-pull-request)
- [License](#license)
- [Authors](#authors)
- [Acknowledgements](#acknowledgements)

## About The Project

Building a hobby OS using modern tools.

## Built With

* [Clang](https://llvm.org/)
* [Meson](https://mesonbuild.com/)
* [Xorriso](https://www.gnu.org/software/xorriso/)
* [Limine](https://github.com/limine-bootloader/limine)

## Getting Started

How to set up this project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

* LLVM
* Xorriso
* QEMU
* Meson

### Installation

1. Clone the repo

```sh
git clone https://github.com/My-Bad-2/pyro.git
```

2. Configure the meson project

```sh
meson setup build --cross-file meta/x86_64-clang.cross-file
```
Note: Change the x86_64-clang.cross-file as necessary for your build

3. Build and run
```sh
cd build && meson compiler
```

## Roadmap

See the [open issues](https://github.com/My-Bad-2/Pyro/issues) for a list of proposed features (and known issues).

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.
* If you have suggestions for adding or removing projects, feel free to [open an issue](https://github.com/My-Bad-2/Pyro/issues/new) to discuss it, or directly create a pull request after you edit the *README.md* file with necessary changes.
* Please make sure you check your spelling and grammar.
* Create individual PR for each suggestion.
* Please also read through the [Code Of Conduct](https://github.com/My-Bad-2/Pyro/blob/main/docs/CODE_OF_CONDUCT.md) before posting your first idea as well.

### Creating A Pull Request

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Detail changes made in [Changelog](Changelog)
5. Push to the Branch (`git push origin feature/AmazingFeature`)
6. Open a Pull Request

## License

Distributed under the MIT License. See [LICENSE](https://github.com/My-Bad-2/Pyro/blob/main/LICENSE.md) for more information.

## Authors

* **My-Bad-2** - [My-Bad-2](https://github.com/My-bad-2/)

## Acknowledgements

* [Limine](https://github.com/limine-bootloader/limine)
* [Eyalroz/printf](https://github.com/eyalroz/printf)
* [osdev wiki](https://wiki.osdev.org/Main_Page)
