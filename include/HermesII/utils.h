#pragma once

#include <tiramisu/tiramisu.h>
#include <tiramisu/auto_scheduler/evaluator.h>
#include <tiramisu/auto_scheduler/search_method.h>

#include <chrono>
#include <sqlite3.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

enum Operation
{
    legality = 0,
    execution = 1,
    annotations = 2,
    skewing_solver = 3,
};

struct Result
{
    std::string name;
    bool legality;
    std::string isl_ast;
    std::string exec_times;
    std::string additional_info;
    bool success;
};

inline bool file_exists(const std::string &name);

bool apply_action(std::string, tiramisu::function *, Result &);

std::string get_first_comp(std::string comps_str);

std::vector<tiramisu::computation *> get_comps(std::string comps_str, tiramisu::function *implicit_function);

tiramisu::computation *get_computation_by_name(std::string comp_name, tiramisu::function *implicit_function);

bool apply_actions_from_schedule_str(std::string schedule_str, tiramisu::function *implicit_function, Result &);

bool isSingleQuoteOrWhiteSpace(char c);

int write_wrapper(std::string function_name);

std::tuple<bool, std::string> exec(const char *cmd);

// std::map<std::string, std::function<Result(std::string, Operation)>> createFuncMap();
std::map<int, std::function<Result(std::string, std::string, Operation)>> createSwitchMap();

Operation get_operation_from_string(std::string operation_str);

std::string serialize_result(Result &result);

void schedule_str_to_result_str(std::string function_name, std::string schedule_str, Operation operation, std::vector<tiramisu::buffer *> buffers);