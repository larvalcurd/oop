namespace TVSetApp.Commands;
public class TurnOnCommand : ICommand
{
    public string Name => "TurnOn";

    public void Execute(TVSet tv, string[] args)
    {
        tv.TurnOn();
        Console.WriteLine("TV is turned on");
    }
}