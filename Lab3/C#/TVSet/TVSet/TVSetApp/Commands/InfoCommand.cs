namespace TVSetApp.Commands;

public class InfoCommand : ICommand
{
    public string Name => "Info";

    public void Execute(TVSet tv, string[] args)
    {
        if (tv.IsOn)
        {
            Console.WriteLine($"TV is turned on");
            Console.WriteLine($"Channel is: {tv.GetChannel()}");
            foreach (var (channel, name) in tv.GetAllChannelNames())
            {
                Console.WriteLine($"{channel} - {name}");
            }
        }
        else
        {
            Console.WriteLine("TV is turned off");
        }
    }
}