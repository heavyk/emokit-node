{
  "targets": [
    {
      "target_name": "emokit",
      "sources": [
        "node/emokit_node.cc",
        "c/src/emokit.c",
        "c/src/emokit_libusb.c"
      ],
      "conditions": [
        [
          "OS!=\"win\"",
          {
            "link_settings": {
              "libraries": [
                "<!@(pkg-config --libs libusb-1.0)",
                "<!@(libmcrypt-config --libs)"
              ]
            },
            "cflags": [
              "<!@(pkg-config --cflags libusb-1.0)",
              "<!@(libmcrypt-config --cflags)"
            ]
          }
        ]
      ],
      "include_dirs": [
        "c/include"
      ]
    }
  ]
}
