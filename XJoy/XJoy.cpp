#include "stdafx.h"
#include "Windows.h"
#include "ViGEmClient.h"
#include <iostream>
#include <string>

std::string vigem_error_to_string(VIGEM_ERROR err) {
  switch (err) {
    case VIGEM_ERROR_NONE:
      return "none";
    case VIGEM_ERROR_ALREADY_CONNECTED:
      return "already connected";
    case VIGEM_ERROR_BUS_ACCESS_FAILED:
      return "bus access failed";
    case VIGEM_ERROR_BUS_ALREADY_CONNECTED:
      return "bus already connected";
    case VIGEM_ERROR_BUS_NOT_FOUND:
      return "bus not found";
    case VIGEM_ERROR_BUS_VERSION_MISMATCH:
      return "bus version mismatch";
    case VIGEM_ERROR_CALLBACK_ALREADY_REGISTERED:
      return "callback already registered";
    case VIGEM_ERROR_CALLBACK_NOT_FOUND:
      return "callback not found";
    case VIGEM_ERROR_INVALID_TARGET:
      return "invalid target";
    case VIGEM_ERROR_NO_FREE_SLOT:
      return "no free slot";
    case VIGEM_ERROR_REMOVAL_FAILED:
      return "removal failed";
    case VIGEM_ERROR_TARGET_NOT_PLUGGED_IN:
      return "target not plugged in";
    case VIGEM_ERROR_TARGET_UNINITIALIZED:
      return "target uninitialized";
  }
  return "none";
}

int main() {
  std::cout << "XJoy v0.1.0" << std::endl << std::endl;
  PVIGEM_CLIENT client = vigem_alloc();

  std::cout << "initializing..." << std::endl;
  VIGEM_ERROR err = vigem_connect(client);
  if (err == VIGEM_ERROR_NONE) {
    std::cout << " => connected successfully" << std::endl;
  } else {
    std::cout << "connection error: " << vigem_error_to_string(err) << std::endl;
    std::cout << "exiting..." << std::endl;
    vigem_free(client);
    exit(1);
  }

  PVIGEM_TARGET target = vigem_target_x360_alloc();
  vigem_target_add(client, target);
  std::cout << " => added target Xbox 360 Controller" << std::endl;

  Sleep(10000);
  std::cout << "disconnecting and exiting..." << std::endl;
  vigem_target_remove(client, target);
  vigem_target_free(target);
  vigem_disconnect(client);
  vigem_free(client);
}
