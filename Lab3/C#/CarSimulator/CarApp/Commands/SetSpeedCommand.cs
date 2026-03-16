namespace CarApp.Commands;

public class SetSpeedCommand : ICommand
{
    public string Name => "SetSpeed";

    public void Execute(Car.Car car, string[] args)
    {
        if (args.Length < 1 || !int.TryParse(args[0], out int speed))
        {
            Console.WriteLine("Invalid command argument");
            return;
        }

        if (speed < 0)
        {
            Console.WriteLine("Speed cannot be negative");
            return;
        }

        if (!car.IsTurnedOn)
        {
            Console.WriteLine("Cannot set speed while engine is off");
            return;
        }

        if (car.GetGear() == Car.Gear.Neutral && speed > car.GetSpeed())
        {
            Console.WriteLine("Cannot accelerate on neutral");
            return;
        }

        if (!car.SetSpeed(speed))
        {
            Console.WriteLine("Speed is out of gear range");
        }
    }
}
