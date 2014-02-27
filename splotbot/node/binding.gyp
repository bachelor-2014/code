{
  "targets": [
    {
      "target_name": "addon",
      "sources":
      ["addon.cc","splotbot_wrapper.cc","../cpp/libraries/cJSON/cJSON.c","../cpp/utils/base64.cpp","../cpp/component.cpp","../cpp/instructionbuffer.cpp",
      "../cpp/camera.cpp", "../cpp/singlesteppermotor.cpp",
      "../cpp/componentinitializer.cpp", "../cpp/splotbot.cpp"],
      "libraries": [
        "<!@(pkg-config --libs --cflags opencv)",
      ],
      "ldflags":[
        "-lm", "-pthread", "-ggdb", "-lcurl"
      ],
      "defines": [ "DEBUG", "_DEBUG" ]
    }
  ]
}
