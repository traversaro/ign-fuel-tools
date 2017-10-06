/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <iostream>

#include <gflags/gflags.h>
#include <ignition/fuel-tools.hh>

DEFINE_bool(h, false, "Show help");
DEFINE_string(s, "https://localhost:4430", "Server name");

int main(int argc, char **argv)
{
  // Simple usage.
  std::string usage("List all models.");
  usage += " Usage:\n  ./modelList <options>\n\n";
  usage += "  Example:\n\t ./modelList -s https://localhost:4430";

  gflags::SetUsageMessage(usage);

  // Parse command line arguments.
  gflags::ParseCommandLineNonHelpFlags(&argc, &argv, true);

  // Show help, if specified.
  if (FLAGS_h)
  {
    gflags::SetCommandLineOptionWithMode("help", "false",
        gflags::SET_FLAGS_DEFAULT);
    gflags::SetCommandLineOptionWithMode("helpshort", "true",
        gflags::SET_FLAGS_DEFAULT);
  }
  gflags::HandleCommandLineHelpFlags();

  // Create a ClientConfig, TODO create this from a yaml file
  ignition::fuel_tools::ClientConfig conf;
  ignition::fuel_tools::ServerConfig srv;
  srv.URL(FLAGS_s);
  srv.LocalName("ignitionfuel");
  conf.AddServer(srv);

  ignition::fuel_tools::FuelClient client(conf);
  for (auto iter = client.Models(); iter; ++iter)
    std::cout << iter->Identification().Name() << std::endl;
}
