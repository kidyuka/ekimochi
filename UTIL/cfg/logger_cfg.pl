{
    DebugLog => {
        type => "text",
        size => 1024 * 1024,
    },

    ColorSensorLog => {
        type => "binary",
        size => 10000,
        data => [
            "red",     "uint16",
            "green",   "uint16",
            "blue",    "uint16",
            "reflect", "uint8",
        ],
    },
};
