const unsigned int IEEE_INITIALIZING = 0;
const unsigned int IEEE_FAULTY = 1;
const unsigned int IEEE_DISABLED = 2;
const unsigned int IEEE_LISTENING = 3;
const unsigned int IEEE_PREMASTER = 4;
const unsigned int IEEE_MASTER = 5;
const unsigned int IEEE_PASSIVE = 6;
const unsigned int IEEE_UNCALIBRATED = 7;
const unsigned int IEEE_SLAVE = 8;

const char *get_IEEE_status(const unsigned int value);