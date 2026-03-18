namespace Car.Tests;

public class CarExamplesTests
{
    [Test]
    public void Example1_EngineOnAndInfo()
    {
        var car = new Car();
        car.TurnOnEngine();
        Assert.That(car.IsTurnedOn, Is.True);
        Assert.That(car.GetDirection(), Is.EqualTo(Direction.StandingStill));
        Assert.That(car.GetSpeed(), Is.EqualTo(0));
        Assert.That(car.GetGear(), Is.EqualTo(Gear.Neutral));
    }

    [Test]
    public void Example2_SetGearAndSpeed()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(15);
        Assert.That(car.IsTurnedOn, Is.True);
        Assert.That(car.GetDirection(), Is.EqualTo(Direction.Forward));
        Assert.That(car.GetSpeed(), Is.EqualTo(15));
        Assert.That(car.GetGear(), Is.EqualTo(Gear.First));
    }

    [Test]
    public void Example3_DecelerateOnNeutral()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(0);
        car.SetSpeed(10);
        Assert.That(car.GetDirection(), Is.EqualTo(Direction.Forward));
        Assert.That(car.GetSpeed(), Is.EqualTo(10));
        Assert.That(car.GetGear(), Is.EqualTo(Gear.Neutral));
    }
}
