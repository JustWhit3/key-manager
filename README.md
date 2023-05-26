<p align="center"><img src="https://github.com/JustWhit3/key-manager/blob/main/img/images/logo_GitHub.svg" height=220></p>

<h3 align="center">A desktop app for password management and creation, developed using Qt.</h3>
<p align="center">
    <img title="v0.0" alt="v0.0" src="https://img.shields.io/badge/version-v0.0-informational?style=flat-square"
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
  - [Password creation state](#password-creation-state)
  - [Options state](#options-state)
  - [Other states](#other-states)
- [Credits](#credits)
  - [Project leaders](#project-leaders)
- [Stargazers over time](#stargazers-over-time)

## Introduction

<p align="center"><img src="https://github.com/JustWhit3/key-manager/blob/main/img/examples/password_manager_state.png" width = "500"></p>

`key-manager` is a cross-platform (Linux/Windows/MacOS) and safe desktop app for password management and creation written in C++20 and developed using [Qt v6.4.2](https://www.qt.io/blog/qt-6.4.2-released). No use of QtCreator was made for development, but only "raw" code written by hand and [CMake](https://cmake.org/) tool for building.

> :warning: Windows compatibility is still work in progress.

Two base features can be accessed through the app:

- Password management system: a password storage tool to safely lock information about given accounts (ex: platform, password, username, etc...). See the [corresponding paragraph](#how-passwords-are-protected) of this README for further information about how passwords are protected.
- Password creation: a tool to generate strong passwords based on several requirements chosen by the user (upper/lower letters only, length, etc...).

All the app files are saved into an hidden directory `~/.key-manager_files` created at the beginning of the first app run.

## How passwords are protected

Work in progress.

## Install and use

### Install

Steps to be reproduced:

**0)** Be sure of having the required Qt version already installed before proceeding with the app installation, since Qt dependency is not taken into account into the CMake deps, since it is too big and too complex to build within the app deps.

**1)** Download one of the [releases](https://github.com/JustWhit3/key-manager/releases) of the repository.

**2)** Unzip and enter the downloaded repository directory.

**3)** Install and compile the game and its dependencies:

```bash
cmake -B build
```

Install:

```bash
sudo cmake --build build --target install
```

> :warning: `sudo` is not required on Windows.

Mandatory prerequisites:

- C++20 standard
- g++ compiler (developed on Ubuntu v22.04.1 with g++ v11.3.0)
- [CMake](https://cmake.org/) (at least version 3.15)
- [Qt](https://www.qt.io/blog/qt-6.4.2-released) library (version 6.4.2)

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

## States

### Menu state

Work in progress.

### Password manager state

Work in progress.

### Password creation state

Work in progress.

### Options state

Work in progress.

### Other states

Work in progress.

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

