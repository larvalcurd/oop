namespace CarApp.Commands;

public class EngineOnCommand : ICommand
{
    public string Name => "EngineOn";

    public void Execute(Car.Car car, string[] args)
    {
        car.TurnOnEngine();
    }
}