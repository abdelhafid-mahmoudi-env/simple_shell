#include "main.h"

char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "env"
};

int (*builtin_func[]) (char **) = {
    &cmd_cd,
    &cmd_help,
    &cmd_exit,
    &cmd_env
};

int shell_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/* Function to launch a program. */
int launch(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* Child process */
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Error forking */
        perror("lsh");
    } else {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

/* Function to execute shell command or launch program. */
int execute(char **args) {
    int i;
    if (args[0] == NULL) {
        /* An empty command was entered */
        return 1;
    }

    for (i = 0; i < shell_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return launch(args);
}

/**
 * command_exists - Checks if a command exists in the PATH
 * @cmd: The command to check
 * Return: 1 if command exists, 0 otherwise
 */
int command_exists(char *cmd) {
    struct stat buffer;
    return (stat(cmd, &buffer) == 0 && (buffer.st_mode & S_IXUSR));
}
