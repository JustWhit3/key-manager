<p align="center"><img src="https://github.com/JustWhit3/key-manager/blob/main/img/images/logo_GitHub.svg" height=220></p>

<h3 align="center">A desktop app for password management and creation, developed using Qt</h3>
<p align="center">
    <img title="v0.3" alt="v0.3" src="https://img.shields.io/badge/version-v0.3-informational?style=flat-square"
    <a href="LICENSE">
        <img title="MIT License" alt="license" src="https://img.shields.io/badge/license-MIT-informational?style=flat-square">
    </a>
	<img title="C++20" alt="C++20" src="https://img.shields.io/badge/c++-20-informational?style=flat-square"><br/>
	<img title="Code size" alt="code size" src="https://img.shields.io/github/languages/code-size/JustWhit3/key-manager?color=red">
	<img title="Repo size" alt="repo size" src="https://img.shields.io/github/repo-size/JustWhit3/key-manager?color=red">
	<img title="Lines of code" alt="total lines" src="https://img.shields.io/tokei/lines/github/JustWhit3/key-manager?color=red"><br/>
  <img title="codeq" alt="codeq" src="https://github.com/JustWhit3/key-manager/actions/workflows/codeql-analysis.yml/badge.svg">
  <img title="doc" alt="doc" src="https://github.com/JustWhit3/key-manager/actions/workflows/DocGenerator.yml/badge.svg">
</p>

## Table of contents

- [Introduction](#introduction)
- [How passwords are protected](#how-passwords-are-protected)
- [Install and use](#install-and-use)
  - [Install](#install)
  - [Debug mode](#debug-mode)
- [States](#states)
  - [Menu state](#menu-state)
  - [Password manager state](#password-manager-state)
  - [Password generator state](#password-generator-state)
  - [Options state](#options-state)
  - [Other states](#other-states)
- [Todo](#todo)
- [Credits](#credits)
  - [Project leaders](#project-leaders)
- [Stargazers over time](#stargazers-over-time)

## Introduction

<p align="center"><img src="https://github.com/JustWhit3/key-manager/blob/main/img/examples/password_manager_state.png" width = "500"></p>
<p align="center"><img src="https://github.com/JustWhit3/key-manager/blob/main/img/examples/password_generator_state.png" width = "500"></p>

`key-manager` is a cross-platform (Linux/Windows/MacOS) and safe desktop app for password management and creation written in C++20 and developed using [Qt v6.4.2](https://www.qt.io/blog/qt-6.4.2-released). No use of QtCreator was made for development, but only "raw" code written by hand and [CMake](https://cmake.org/) tool for building.

The app has been tested with `gcc` and `clang` compilers and required minimum versions are respectively 9.3 and 10. It can be compiled on `MSVC` too of course.

The app offers two services.

- [**Password management**](#password-manager-state): a password storage tool to safely lock information about given accounts (ex: platform, password, username, etc...). See the [corresponding paragraph](#how-passwords-are-protected) of this README for further information about how passwords are protected.
- [**Password creation**](#password-generator-state): a tool to generate strong passwords based on several requirements chosen by the user (upper/lower letters only, length, etc...).

All the app files are saved into an hidden directory `~/.key-manager_files` created at the beginning of the first app run.

All contributions are more than welcome. Before contributing, please look at the [contributing file](https://github.com/JustWhit3/key-manager/blob/main/CONTRIBUTING.md) and pick one of the [todo items](#todo) of the list. To propose ideas post something in the [discussion page](https://github.com/JustWhit3/key-manager/discussions).

The app is and will stay **free**, but if you want to support me with a donation it would be really appreciated!

<a href="https://www.buymeacoffee.com/JustWhit33" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Buy Me A Coffee" height="41" width="174"></a>

## How passwords are protected

A login system is applied to the app and a new password setup is required during the first app run. The inserted user password is encrypted using a [XOR cipher method](https://en.wikipedia.org/wiki/XOR_cipher) and a generated random key of lenght 100 alpha-numerical characters is used for encryption and decryption operations. The encrypted password and the key are then saved into a configuration file `~/.key-manager_files/.key`.

> :warning: there are work in progress plans to find a way to protect these sensitive data from reading.

At every login the user password is required and it is verified the matching among it and the user password of the configuration file, which for this occasion is decrypted using the previously mentioned algorithm and the saved key.

Once a new password is added to the database, it is saved into a [Json](https://it.wikipedia.org/wiki/JavaScript_Object_Notation) file located into the `~/.key-manager_files/passwords` directory, which is created at the first app run. Every password sensitive data (username and password itself) is encrypted using the previous algorithm and the saved key.

Once a password is displayed into the [password manager state](#password-manager-state) it is decrypted and shown in the corresponding interface so only the logged user can see it. Passwords reading is also protected with a toggle system.

## Install and use

### Install

Steps to be reproduced:

**1)** Download one of the [releases](https://github.com/JustWhit3/key-manager/releases) of the repository.

**2)** Unzip and enter the downloaded repository directory.

**3)** Install and compile the game and its dependencies:

```bash
cmake -B build
```

> :warning: The three Qt modules required for the project building (`QtCore`, `QtWidgets` and `QtStateMachine`) will be installed during the build part and in case of Ubuntu installation all the prerequisite packages will be installed with `apt`. The Qt build is supported on Ubuntu, Windows and MacOS. On Windows there may be a [known issue](https://github.com/JustWhit3/key-manager/tree/main/img/images/windows_qt_error.png) related to the Qt building, so if you encounter it proceed with a separated installation of Qt and then build the project.

Install:

```bash
sudo cmake --build build --target install
```

> :warning: `sudo` is not required on Windows.

Mandatory prerequisites:

- C++20 standard
- g++ compiler (developed on Ubuntu v22.04.1 with g++ v11.3.0)
- [CMake](https://cmake.org/) (at least version 3.15)
- [Qt](https://www.qt.io/blog/qt-6.4.2-released) library (version 6.4.2), installed during the app installation.

To run the app:

```bash
key-manager
```

Or if you don't want to install it:

```bash
cmake -B build
sudo cmake --build build
./build/src/key-manager
```

### Debug mode

Debug mode is used from developers to test the app. To build the app in debug mode:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
sudo cmake --build build
```

This will automatically compile unit tests and source code with debug tools (like cppcheck).

Optional prerequisites for debug mode:

- [cppcheck](https://cppcheck.sourceforge.io/)
- [doctest](https://github.com/doctest/doctest)

To run all the tests (unit tests and profiling):

```bash
./build/test/unit_tests/key-manager_unit_tests
```

To run [IWYU](https://github.com/include-what-you-use/include-what-you-use) checks:

```bash
./test/IWYU.sh
```

All the code documentation is generated automatically using [Doxygen](https://www.doxygen.nl/) and is stored [here](https://justwhit3.github.io/key-manager/).

## States

### Menu state

<p align="center"><img src="https://github.com/JustWhit3/key-manager/blob/main/img/examples/menu_state.png" width = "500"></p>

This state contains the main menu of the app and is used to access [password manager](#password-manager-state) and [password creation](#password-creation-state) tools and the [options state](#options-state). App metadata and release information is displayed on the left side. From this state it is possible also to come back to the [login state](#other-states).


### Password manager state

<p align="center"><img src="https://github.com/JustWhit3/key-manager/blob/main/img/examples/password_manager_state.png" width = "500"></p>

This state contains the password manager tool. Here you can add, delete and modify passwords from the database; there is also a third button which gives a more detailed information about a given password. See the [corresponding paragraph](#how-passwords-are-protected) to understand how passwords are keeping safe. Passwords are ordered in alphabetical order and can be searched through the corresponding tool.

### Password generator state

<p align="center"><img src="https://github.com/JustWhit3/key-manager/blob/main/img/examples/password_generator_state.png" width = "500"></p>

This state contains the password generator. Here you can generate strong and safe passwords and save them to clipboard with a click. You can also chose which kind of letters and symbols type you want to use for the password generation.

### Options state

Work in progress.

### Other states

Other states are:

- Add password state:

<p align="center"><img src="https://github.com/JustWhit3/key-manager/blob/main/img/examples/set_password_state.png" width = "500"></p>

- Login state:

<p align="center"><img src="https://github.com/JustWhit3/key-manager/blob/main/img/examples/login_state.png" width = "500"></p>

- Set new password state: work in progress.

## Todo

- Add setup to password recovery in case of troubles.
- Add possibility to change the app password.
- Improve the encryption algorithm.
- Add the options state.
- Add sounds.
- Add (maybe) animations in transitions among states.

## Credits

### Project leaders

<table>
  <tr>
    <td align="center"><a href="https://justwhit3.github.io/"><img src="https://avatars.githubusercontent.com/u/48323961?v=4" width="100px;" alt=""/><br /><sub><b>Gianluca Bianco</b></sub></a></td>
  </tr>
</table>

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

## Stargazers over time

[![Stargazers over time](https://starchart.cc/JustWhit3/key-manager.svg)](https://starchart.cc/JustWhit3/key-manager)
