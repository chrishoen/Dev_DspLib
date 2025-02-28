#pragma once

/*==============================================================================
file paths.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include <memory>

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants. File identifiers.

// File codes.
static const int cFile_SignalHistoryCsv = 101;
static const int cFile_AlphaHistoryCsv = 102;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

// Initialize. This must be called after the program directory is set.
void initialize_paths();
void finalize_paths();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

// Return a directory path.
const char* get_filesdir();
const char* get_datadir();
const char* get_logdir();

// Return a file path relative to a directory path.
const char* get_files_filepath(char* aBuffer, const char* aFileName);
const char* get_data_filepath(char* aBuffer, const char* aFileName);
const char* get_log_filepath(char* aBuffer, const char* aFileName);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

// Create a new string and fill it with a file path relative to a directory
// path.
std::unique_ptr<std::string> get_files_filepath(const char* aFileName);
std::unique_ptr<std::string> get_data_filepath(const char* aFileName);
std::unique_ptr<std::string> get_log_filepath(const char* aFileName);

// Create a new string and fill it with a file path that is determined
// by a file identifier.
std::unique_ptr<std::string> get_filepath_from_id(int aFileId);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

void paths_test1();
void paths_show();

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

