#!/usr/bin/env sh
adb install -r bin/CarGame-debug.apk
adb shell am start -n org.oxygine.CarGame/org.oxygine.CarGame.MainActivity
