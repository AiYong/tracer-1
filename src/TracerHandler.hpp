/* Copyright (c) 2017, Daniel Mensinger
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Daniel Mensinger nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Daniel Mensinger BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "defines.hpp"
#include "AbstractPrinter.hpp"
#include "PrinterContainer.hpp"
#include "Tracer.hpp"
#include <signal.h>
#include <vector>

namespace tracer {

class TracerHandler final {
 public:
  typedef void (*callBackPTR)(Tracer *tracer, AbstractPrinter *printer, void *userData);

  struct Config {
    std::vector<TraceerEngines>  preferredTracerEngines;   //!< List of preferred engines; First try them for the Tracer
    std::vector<DebuggerEngines> preferredDebuggerEngines; //!< List of preferred engines; First try them for the Tracer

    bool        autoPrintToStdErr = true;        //!< Prints the stack trace to stderr when enabled
    bool        autoPrintToFile   = false;       //!< Automatically writes the stack trace to a file when enabled
    std::string logFile           = "trace.log"; //!< The file to automatically print to; Requires autoPrintToFile
    bool        appendToFile      = true;        //!< Overides file co; Requires autoPrintToFile

    callBackPTR callback     = nullptr; //!< Function pointer to be called in the internal signal handler (MUST return)
    void *      callbackData = nullptr; //!< User defined data to be send to the callback function

    bool callDefultHandlerWhenDone = true; //!< The signal handler will call the default signal handler when done

    //! List of signals to handle
    std::vector<int> signums = {SIGINT,
                                SIGILL,
                                SIGABRT,
                                SIGFPE,
                                SIGSEGV,
                                SIGTERM,
#ifndef _WIN32
                                SIGQUIT,
                                SIGTRAP,
                                SIGBUS,
                                SIGPIPE,
                                SIGSYS
#endif
    };
  };

 private:
  static TracerHandler *tracer;
  PrinterContainer      printer;

  Config cfg;

  static void sigHandler(int sigNum);

  TracerHandler();

 public:
  ~TracerHandler();

  static TracerHandler *getTracer();
  static void           reset();

  Config getConfig() const { return cfg; }
  void setConfig(Config c) { cfg = c; }

  bool setup(PrinterContainer printerToUse);
  bool defaultSetup();
};
}
