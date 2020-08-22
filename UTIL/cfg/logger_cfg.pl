{
    ColorSensorLog => {
        type => "binary",
        size => 10000,
        data => [
            "red",     "uint16_t",
            "green",   "uint16_t",
            "blue",    "uint16_t",
            "reflect", "uint8_t",
        ],
    },

    DebugLog => {
        type => "text",
        size => 1024 * 256,
    },
};
