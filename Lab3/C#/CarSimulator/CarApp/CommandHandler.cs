using CarApp.Commands;

public class CommandHandler
{
    private readonly Dictionary<string, ICommand> _commands;

    public CommandHandler()
    {
        _commands = new Dictionary<string, ICommand>
        {
            { "EngineOn", new EngineOnCommand() },
            { "EngineOff", new EngineOffCommand() },
            { "Info", new InfoCommand() },
            { "SetGear", new SetGearCommand() },
            { "SetSpeed", new SetSpeedCommand() },
        };
    }

    public void HandleCommand(Car.Car car, string input)
    {
        var parts = input.Split(' ', StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length == 0)
        {
            Console.WriteLine("No command entered");
            return;
        }

        var commandName = parts[0];
        var args = parts.Skip(1).ToArray();

        if (_commands.TryGetValue(commandName, out var command))
        {
            command.Execute(car, args);
        }
        else
        {
            Console.WriteLine($"Unknown command");
        }
    }
}
