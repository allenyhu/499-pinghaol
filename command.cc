#include "serviceClient.h"

int main(int argc, char** argv) {
  ServiceLayerClient test(grpc::CreateChannel(
      "localhost:50002", grpc::InsecureChannelCredentials()));
  string array[7];
  string curr;
  if (argc <= 7) {
    for (int i = 0; i < argc; i++) {
      array[i] = argv[i];
    }

    if (argc == 3) {
      if (array[1] == "--register") {
        test.registeruser(array[2]);
      } else if (array[1] == "--read") {
        test.read(stoi(array[2]));
      } else {
        cout << "Invalid command-line flags" << endl;
      }
    } else if (argc == 4) {
      if (array[1] == "--user" && array[3] == "--monitor") {
        curr = array[2];
        test.monitor(curr);
      } else {
        cout << "Invalid command-line flags" << endl;
      }
    } else if (argc == 5) {
      if (array[1] == "--user") {
        curr = array[2];
      }
      if (array[3] == "--chirp") {
        test.chirp(curr, array[4], "");
      } else if (array[3] == "--follow") {
        test.follow(curr, array[4]);
      } else if (array[3] == "--stream") {
        test.stream(curr, array[4]);
      } else {
        cout << "Invalid command-line flags" << endl;
      }
    } else if (argc == 7) {
      if (array[1] == "--user" && array[3] == "--chirp" &&
          array[5] == "--reply") {
        curr = array[2];
        test.chirp(curr, array[4], array[6]);
      } else {
        cout << "Invalid command-line flags" << endl;
      }
    } else {
      cout << "Invalid command-line flags" << endl;
    }
  } else {
    cout << "Too many argument" << endl;
  }
  return 0;
}
