namespace CarApp.Commands;

public class EngineOffCommand : ICommand
{
    public string Name => "EngineOff";

    public void Execute(Car.Car car, string[] args)
    {
        if (!car.TurnOffEngine())
        {
            Console.WriteLine("Car must be stopped and in neutral gear");
        }
    }
}