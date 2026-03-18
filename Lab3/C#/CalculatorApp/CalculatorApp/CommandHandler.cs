using CalculatorApp.Commands;

namespace CalculatorApp;

public class CommandHandler
{
    private readonly Dictionary<string, ICommand> _commands = new();
    private readonly Calculator.Calculator _calculator = new();

    public CommandHandler()
    {
        RegisterCommand(new VarCommand());
        RegisterCommand(new LetCommand());
        RegisterCommand(new FnCommand());
        RegisterCommand(new PrintCommand());
        RegisterCommand(new PrintVarsCommand());
        RegisterCommand(new PrintFnsCommand());
    }

    private void RegisterCommand(ICommand command)
    {
        _commands[command.Name] = command;
    }

    public void Handle(string input)
    {
        input = input.Trim();
        if (string.IsNullOrEmpty(input))
            return;

        // Разделяем на команду и аргументы
        // "var x" → commandName = "var", arguments = "x"
        // "printvars" → commandName = "printvars", arguments = ""
        
        int spaceIndex = input.IndexOf(' ');
        
        string commandName;
        string arguments;
        
        if (spaceIndex == -1)
        {
            // Нет пробела — вся строка это команда
            commandName = input;
            arguments = "";
        }
        else
        {
            commandName = input.Substring(0, spaceIndex);
            arguments = input.Substring(spaceIndex + 1);
        }

        if (_commands.TryGetValue(commandName, out var command))
        {
            command.Execute(_calculator, arguments);
        }
        else
        {
            Console.WriteLine("Unknown command");
        }
    }
}