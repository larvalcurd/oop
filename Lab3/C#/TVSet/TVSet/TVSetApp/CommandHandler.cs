using TVSetApp;
using TVSetApp.Commands;

public class CommandHandler
{
    private readonly TVSet _tv = new();
    private readonly Dictionary<string, ICommand> _commands = new();

    public CommandHandler()
    {
        RegisterCommand(new TurnOnCommand());
        RegisterCommand(new TurnOffCommand());
        RegisterCommand(new SelectChannelCommand());
        RegisterCommand(new SelectPreviousChannelCommand());
        RegisterCommand(new InfoCommand());
        RegisterCommand(new SetChannelNameCommand());
        RegisterCommand(new DeleteChannelNameCommand());
        RegisterCommand(new GetChannelNameCommand());
        RegisterCommand(new GetChannelByNameCommand());
    }

    private void RegisterCommand(ICommand command)
    {
        _commands[command.Name] = command;
    }

    public void HandleCommand(string input)
    {
        var parts = input.Split(' ', StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length == 0) return;

        var commandName = parts[0];
        var args = parts.Skip(1).ToArray();

        if (_commands.TryGetValue(commandName, out var command))
        {
            command.Execute(_tv, args);
        }
        else
        {
            Console.WriteLine("ERROR");
        }
    }
}