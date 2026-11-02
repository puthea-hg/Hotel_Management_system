#pragma once

#include <string>

// Reads an integer menu choice in [minimum, maximum].
// Returns -1 if input reaches EOF.
int readMenuChoice(const std::string& prompt, int minimum, int maximum);