/*
 * executeShellCommand.hpp
 *
 *  Created on: Feb 18, 2021
 *      Author: Samuel Carrasco
 */

#ifndef EXECUTESHELLCOMMANDS_H_
#define EXECUTESHELLCOMMANDS_H_

#include <iostream>
#include <string>
#include <vector>
#include "command.hpp"
#include "parser.hpp"

// Executes a shell command. Returns 0 for a successful command and 1 for a failed command.
int executeShellCommand(shell_command shellCommand);

#endif
