namespace Car.Tests;

public class Tests
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

    public void TurnOnEngine_WhenEngineIsOff_ReturnsTrue()
    {
        var car = new Car();

        bool result = car.TurnOnEngine();

        Assert.That(result, Is.True);
        Assert.That(car.IsTurnedOn, Is.True);
    }

    public void TurnOnEngine_WhenEngineIsAlreadyOn_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();

        bool result = car.TurnOnEngine();

        Assert.That(result, Is.True);
    }

    public void TurnOffEngine_WhenOnAndNeutralAndStopped_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();

        bool result = car.TurnOffEngine();

        Assert.That(result, Is.True);
        Assert.That(car.IsTurnedOn, Is.False);
    }

    [Test]
    public void TurnOffEngine_WhenAlreadyOff_ReturnsTrue()
    {
        var car = new Car();

        bool result = car.TurnOffEngine();

        Assert.That(result, Is.True);
    }

    [Test]
    public void SetGear_EngineOff_ToNeutral_ReturnsTrue()
    {
        var car = new Car();

        bool result = car.SetGear(0);

        Assert.That(result, Is.True);
    }

    [Test]
    public void SetGear_EngineOff_ToFirst_ReturnsFalse()
    {
        var car = new Car();

        bool result = car.SetGear(1);

        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_EngineOn_ToFirst_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();

        bool result = car.SetGear(1);

        Assert.That(result, Is.True);
        Assert.That(car.GetGear(), Is.EqualTo(Gear.First));
    }

    [Test]
    public void SetGear_InvalidGear_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();

        bool result = car.SetGear(6);

        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_ToReverse_WhenStopped_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();

        bool result = car.SetGear(-1);

        Assert.That(result, Is.True);
        Assert.That(car.GetGear(), Is.EqualTo(Gear.Reverse));
    }

    [Test]
    public void SetSpeed_EngineOff_ReturnsFalse()
    {
        var car = new Car();

        bool result = car.SetSpeed(10);

        Assert.That(result, Is.False);
    }

    [Test]
    public void SetSpeed_NegativeSpeed_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);

        bool result = car.SetSpeed(-10);

        Assert.That(result, Is.False);
    }

    [Test]
    public void SetSpeed_InGearRange_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);

        bool result = car.SetSpeed(15);

        Assert.That(result, Is.True);
        Assert.That(car.GetSpeed(), Is.EqualTo(15));
    }

    [Test]
    public void SetSpeed_OutOfGearRange_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);

        bool result = car.SetSpeed(50);

        Assert.That(result, Is.False);
        Assert.That(car.GetSpeed(), Is.EqualTo(0));
    }

    [Test]
    public void SetSpeed_OnNeutral_CanDecelerate()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(20);
        car.SetGear(0);

        bool result = car.SetSpeed(10);

        Assert.That(result, Is.True);
        Assert.That(car.GetSpeed(), Is.EqualTo(10));
    }

    [Test]
    public void SetSpeed_OnNeutral_CannotAccelerate()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(20);
        car.SetGear(0);

        bool result = car.SetSpeed(25);

        Assert.That(result, Is.False);
        Assert.That(car.GetSpeed(), Is.EqualTo(20));
    }

    [Test]
    public void Direction_WhenMovingForward_IsForward()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);

        Assert.That(car.GetDirection(), Is.EqualTo(Direction.Forward));
    }

    [Test]
    public void Direction_WhenMovingBackward_IsBackward()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);

        Assert.That(car.GetDirection(), Is.EqualTo(Direction.Backward));
    }

    [Test]
    public void Direction_WhenStopped_IsStandingStill()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetSpeed(0);

        Assert.That(car.GetDirection(), Is.EqualTo(Direction.StandingStill));
    }

    [Test]
    public void Direction_MovingBackwardOnNeutral_StaysBackward()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(15);
        car.SetGear(0);

        car.SetSpeed(10);

        Assert.That(car.GetDirection(), Is.EqualTo(Direction.Backward));
        Assert.That(car.GetSpeed(), Is.EqualTo(10));
    }

    [Test]
    public void SetGear_FromReverseToFirst_WhenMoving_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);

        bool result = car.SetGear(1);

        Assert.That(result, Is.False);
        Assert.That(car.GetGear(), Is.EqualTo(Gear.Reverse));
    }

    [Test]
    public void SetGear_FromReverseToFirst_WhenStopped_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        car.SetSpeed(0);

        bool result = car.SetGear(1);

        Assert.That(result, Is.True);
    }

    [Test]
    public void SetGear_FromNeutralToFirst_WhenMovingBackward_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        car.SetGear(0);

        bool result = car.SetGear(1);

        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_SpeedOutOfNewGearRange_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(15);

        bool result = car.SetGear(2);

        Assert.That(result, Is.False);
    }

    [Test]
    public void SetGear_SpeedInNewGearRange_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(25);

        bool result = car.SetGear(2);

        Assert.That(result, Is.True);
        Assert.That(car.GetGear(), Is.EqualTo(Gear.Second));
    }

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

    [Test]
    public void Example4_CannotTurnOffWhileMoving()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);

        bool result = car.TurnOffEngine();

        Assert.That(result, Is.False);
        Assert.That(car.IsTurnedOn, Is.True);
    }

    [Test]
    public void Example5_CannotSetGearOutOfSpeedRange()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(19);

        bool result = car.SetGear(2);

        Assert.That(result, Is.False);
        Assert.That(car.GetGear(), Is.EqualTo(Gear.First));
    }
}
