![TinyGS Logo](doc/images/TinyGS_logo.png)

TinyGS is an open network of Ground Stations distributed around the world to receive and operate LoRa satellites, weather probes and other flying objects, using cheap and versatile modules.

**This is a fork of the TinyGS repository. If you are looking for the official repository, official firmware releases and documentation see [github.com/G4lile0/tinyGS](https://github.com/G4lile0/tinyGS)**

## Releases

![Build](https://github.com/mdkendall/tinyGS/actions/workflows/build-platformio.yml/badge.svg)

The upstream repository has a <code>master</code> branch from which the official releases are compiled, and a <code>beta</code> branch where development is ongoing. There are no precompiled releases from the <code>beta</code> branch. The <code>master</code> branch is curently well behind the <code>beta</code> branch.

The <code>latest</code> release provided in this fork is the result of compiling the <code>beta</code> branch plus:

- [Pull Request 177](https://github.com/G4lile0/tinyGS/pull/177) Add battery voltage monitoring feature
- [Pull Request 178](https://github.com/G4lile0/tinyGS/pull/178) Add GitHub action to build firmware
- [Pull Request 182](https://github.com/G4lile0/tinyGS/pull/182) Handle no OLED reset pin

If you would like to use the latest firmware on your TinyGS station without having to compile it from source yourself, this release may be of interest.
