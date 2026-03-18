namespace Car.Tests;

public class CarInitializationTests
{
    [Test]
    public void NewCar_EngineIsOff()
    {
        var car = new Car();
        Assert.That(car.IsTurnedOn, Is.False);
    }

    [Test]
    public void NewCar_GearIsNeutral()
    {
        var car = new Car();
        Assert.That(car.GetGear(), Is.EqualTo(Gear.Neutral));
    }

    [Test]
    public void NewCar_SpeedIsZero()
    {
        var car = new Car();
        Assert.That(car.GetSpeed(), Is.EqualTo(0));
    }

    [Test]
    public void NewCar_DirectionIsStandingStill()
    {
        var car = new Car();
        Assert.That(car.GetDirection(), Is.EqualTo(Direction.StandingStill));
    }
}
