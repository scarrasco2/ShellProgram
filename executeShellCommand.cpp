/*
 * executeShellCommand.cpp
 *
 *  Created on: Feb 18, 2021
 *      Author: Samuel Carrasco
 */

// Standard C libraries
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/wait.h>

// Defined libraries for the shell program
#include "command.hpp"
#include "parser.hpp"
#include "executeShellCommand.hpp"

// Macros for easy reading in code
#define CHILD_ID 0
#define SUCCESSFUL 0
#define FAILED 2

// Helper function to convert cmd object to a pointer to use in execvp function
int exec(const std::string &cmd, const std::vector<std::string> &args) {
	// Make an ugly C-style args array.
	std::vector<char*> c_args = { const_cast<char*>(cmd.c_str()) };
	for (const auto &a : args) {
		c_args.push_back(const_cast<char*>(a.c_str()));
	}
	c_args.push_back(nullptr);

	return execvp(cmd.c_str(), c_args.data());
}

int executeShellCommand(shell_command cmd) {
	int child_id = fork();
	const char *coutFile = (cmd.cout_file).c_str();
	const char *cinFile = (cmd.cin_file).c_str();
	int fdOut;
	if (cmd.cout_mode == ostream_mode::append) {
		fdOut = open(coutFile, O_RDWR | O_APPEND, 0644);
	} else {
		fdOut = open(coutFile, O_CREAT | O_WRONLY, 0644);
	}

	int fdIn = open(cinFile, O_RDONLY);

	if (child_id < CHILD_ID) {
		fprintf(stderr, "Fork failed \n");
		exit(1);
	}

	else if (child_id == CHILD_ID) {
		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		exec(cmd.cmd, cmd.args);
		exit(1);
	}

	else {
		int status;
		wait(&status);
		int exit_status = WEXITSTATUS(status);
		if ((cmd.next_mode == next_command_mode::on_success)
				&& (exit_status == FAILED)) {
			return FAILED;
		}
		if ((cmd.next_mode == next_command_mode::on_fail)
				&& (exit_status == SUCCESSFUL)) {
			return FAILED;
		}

	}
	return SUCCESSFUL;
}
