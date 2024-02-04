#include <libnotify/notify.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define EXIT_NO_BAT 1
#define EXIT_PERM 2

char *program_name = "poweroff";

int checkBat(FILE *file) {

  int capacity = -1;
  if (fscanf(file, "%d", &capacity) == 0) {
    fprintf(stderr, "Error No battery found");
    exit(EXIT_NO_BAT);
  }
  sleep(capacity * 10);
  fflush(file);
  fseek(file, 0, SEEK_SET);
  return capacity;
}

void pushNoti(int val) {
  bool notifyInitStatus = notify_init(program_name);
  char noti[100];
  sprintf(noti, "Your system battery is running low at %d", val);
  NotifyNotification *Bat =
      notify_notification_new("Low Battery", noti, "dialog-information");
  notify_notification_show(Bat, NULL);
  g_object_unref(G_OBJECT(Bat));
  notify_uninit();
}

int main(int argc, char **argv) {

  FILE *file;
  int val;
  // TODO: relavtive file path.
  file = fopen("/sys/class/power_supply/BAT0/capacity", "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening the file. Check permission");
    exit(EXIT_PERM);
  }
  // TODO: Check if charging then sleep or quit.
  while (true) {
    val = checkBat(file);
    if (val <= 20) {
      pushNoti(val);
    }
  }
  fclose(file);
  return 1;
}
