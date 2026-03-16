namespace CarApp.Commands;

public class InfoCommand : ICommand
{
    public string Name => "Info";

    public void Execute(Car.Car car, string[] args)
    {
        string engineState = car.IsTurnedOn ? "on" : "off";
        
        string direction = car.GetDirection() switch
        {
            Car.Direction.Forward => "forward",
            Car.Direction.Backward => "backward",
            _ => "standing still"
        };
        
        Console.WriteLine($"Engine: {engineState}");
        Console.WriteLine($"Direction: {direction}");
        Console.WriteLine($"Speed: {car.GetSpeed()}");
        Console.WriteLine($"Gear: {(int)car.GetGear()}");
    }
}