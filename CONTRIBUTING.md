# Contributing

## Table of contents

- [Introduction](#introduction)
- [How to contribute](#how-to-contribute)
- [How to raise an issue](#how-to-raise-an-issue)

## Introduction

Thank you very much for being here! First of all, I want to let you know that contributions are more than welcome and really appreciated.

In case you want to contribute, even with a small bug fix, you will be featured into the credits list.

## How to contribute

To add your contribution, please follow these guidelines:

1) Fork your own copy of the repository.
2) Work on your changes / improvements in the forked repo.
3) **Test** if your changes / improvements are correctly implemented and all the other features are not compromised. For this latter requirement, please run this script:

```bash
./tests/all_tests.sh
./tests/IWYU.sh
```

> :warning: the [IWYU](https://github.com/include-what-you-use/include-what-you-use) tool may detect wrong errors sometimes.

and possibly update also the respective files with your news tests, if necessary.

5) Before submitting the code, reformat it using the [`.clang-format`](https://github.com/JustWhit3/snake-game/blob/main/.clang-format.md) file. Simply do:

```bash
.clang-format -i /path/to/file
```

5) Optional, but really appreciated: update the [documentation](https://justwhit3.github.io/key-manager/) (directly while writing the code) and the main [README](https://github.com/JustWhit3/key-manager/blob/main/README.md) with the new features you added.
6) Finally, make the pull request. The Doxygen page will be updated automatically.

Once your pull request will be submitted, I will carefully review it and, if it will be considered as an improvement, I will confirm it.

## How to raise an issue

For a new feature request see [here](https://github.com/JustWhit3/key-manager/blob/main/.github/ISSUE_TEMPLATE/feature_request.md).
For a bug report see [here](https://github.com/JustWhit3/key-manager/blob/main/.github/ISSUE_TEMPLATE/bug_report.md).
