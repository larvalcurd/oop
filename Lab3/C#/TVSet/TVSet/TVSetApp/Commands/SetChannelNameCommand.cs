namespace TVSetApp.Commands;

public class SetChannelNameCommand : ICommand
{
    public string Name => "SetChannelName";

    public void Execute(TVSet tv, string[] args)
    {
        if (args.Length < 2 || !int.TryParse(args[0], out int channel))
        {
            Console.WriteLine("ERROR");
            return;
        }

        string name = string.Join(" ", args.Skip(1));
        
        if (tv.SetChannelName(channel, name))
        {
            Console.WriteLine($"Channel name set: {channel} - {name}");
        }
        else
        {
            Console.WriteLine("ERROR");
        }
    }
}