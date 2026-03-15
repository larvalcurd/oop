namespace TVSetApp.Commands;

public class GetChannelByNameCommand : ICommand
{
    public string Name => "GetChannelByName";

    public void Execute(TVSet tv, string[] args)
    {
        if (args.Length < 1)
        {
            Console.WriteLine("ERROR");
            return;
        }

        string channelName = string.Join(" ", args);
        int? channelNumber = tv.GetChannelByName(channelName);

        if (channelNumber != 0 && channelNumber.HasValue)
        {
            Console.WriteLine($"Channel for name {channelName}: {channelNumber.Value}");
        }
        else
        {
            Console.WriteLine("ERROR");
        }
    }
}