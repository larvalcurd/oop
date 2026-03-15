namespace TVSetApp.Commands;

public class GetChannelNameCommand : ICommand
{
    public string Name => "GetChannelName";

    public void Execute(TVSet tv, string[] args)
    {
        if (args.Length < 1 || !int.TryParse(args[0], out int channel))
        {
            Console.WriteLine("ERROR");
            return;
        }

        string? channelName = tv.GetChannelName(channel);
        if (channelName != null)
        {
            Console.WriteLine($"Channel {channel} name: {channelName}");
        }
        else
        {
            Console.WriteLine("ERROR");
        }
    }
}