    namespace Car;

    public enum Direction
    {
        StandingStill,
        Forward,
        Backward
    }

    public enum Gear
    {
        Reverse = -1,
        Neutral = 0,
        First = 1,
        Second = 2,
        Third = 3,
        Fourth = 4,
        Fifth = 5
    }

    public class Car
    {
        public static readonly Dictionary<Gear, (int MinSpeed, int MaxSpeed)> GearSpeedRanges = new()
        {
            { Gear.Reverse, (0, 20) },
            { Gear.Neutral, (0, 150) },
            { Gear.First, (0, 30) },
            { Gear.Second, (20, 50) },
            { Gear.Third, (30, 60) },
            { Gear.Fourth, (40, 90) },
            { Gear.Fifth, (50, 150) }
        };

        private bool _engineOn = false;
        private Gear _gear = Gear.Neutral;
        private int _speed = 0;
        private Direction _direction = Direction.StandingStill;

        public bool IsTurnedOn => _engineOn;
        public Gear GetGear() => _gear;
        public int GetSpeed() => _speed;
        public Direction GetDirection() => _direction;

        public bool TurnOnEngine()
        {
            if (_engineOn)
            {
                return true;
            }

            _engineOn = true;
            return true;
        }

        public bool TurnOffEngine()
        {
            if (_gear != Gear.Neutral || _speed != 0)
            {
                return false;
            }

            _engineOn = false;
            return true;
        }
        public bool SetGear(int gear)
        {
            if (gear < -1 || gear > 5)
            {
                return false;
            }

            if (!_engineOn && gear != 0)
            {
                return false;
            }

            if (gear == -1 && _speed != 0)
            {
                return false;
            }

            if (gear > 0 && _direction == Direction.Backward)
            {
                return false;
            }

            Gear newGear = (Gear)gear;
            var range = GearSpeedRanges[newGear];
            if (_speed < range.MinSpeed || _speed > range.MaxSpeed)
            {
                return false;
            }

            _gear = newGear;
            return true;
        }

        public bool SetSpeed(int speed)
        {
            if (speed < 0 || speed > 150)
            {
                return false;
            }

            if (!_engineOn)
            {
                return false;
            }

            if (_gear == Gear.Neutral && speed > _speed)
            {
                return false;
            }

            if (speed < GearSpeedRanges[_gear].MinSpeed || speed > GearSpeedRanges[_gear].MaxSpeed)
            {
                return false;
            }

            _speed = speed;

            if (_speed == 0)
            {
                _direction = Direction.StandingStill;
            }
            else if (_gear == Gear.Reverse)
            {
                _direction = Direction.Backward;
            }
            else if (_direction == Direction.StandingStill)
            {
                _direction = Direction.Forward;
            }

            return true;
        }
    }
