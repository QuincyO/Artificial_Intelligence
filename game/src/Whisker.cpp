

class Agent
{
public:


    Agent(float r1, float r2, float l1, float l2, float maxAccel, float maxSpeed)
    {
        m_fish = new RigidBody();
        m_maxAacceleration = maxAccel;
        m_maxSpeed = maxSpeed;
        whiskerLengthL1 = l1;
        whiskerLengthL2 = l2;
        whiskerLengthR1 = r1;
        whiskerLengthR2 = r2;
        m_fish->angularSpeed = 100;

        whiskers = new Vector2[whiskerCount];
        detection = new bool[whiskerCount];

    }

    ~Agent()
    {
        delete m_fish;
        m_fish = nullptr;
    }





    void Avoid(Vector2 obstacle, float deltaTime, float radiusOfObstacle)
    {
        //direction = Rotate(direction, 50 * dt * DEG2RAD);

        for (int i = 0; i < whiskerCount; i++)
        {
            detection[i] = CheckCollisionLineCircle(m_fish->pos, obstacle, whiskers[i], radiusOfObstacle);
        }

        if (detection[1] || detection[0])
        {
            m_fish->velo = Rotate(m_fish->velo, m_fish->angularSpeed * deltaTime * DEG2RAD);
        }

        if (detection[2] || detection[3])
        {
            m_fish->velo = Rotate(m_fish->velo, -m_fish->angularSpeed * deltaTime * DEG2RAD);
        }

    }

    void UpdateWhiskers()
    {
        whiskerAngleL1 = fmodf(m_fish->rotation - 15 + 360, 360.0f);
        whiskerAngleL2 = fmodf(m_fish->rotation - 30 + 360, 360.0f);
        whiskerAngleR1 = fmodf(m_fish->rotation + 15 + 360, 360.0f);
        whiskerAngleR2 = fmodf(m_fish->rotation + 30 + 360, 360.0f);


        whiskers[0] = VectorFromAngleDegrees(whiskerAngleL1) * whiskerLengthL1;
        whiskers[1] = VectorFromAngleDegrees(whiskerAngleL2) * whiskerLengthL2;
        whiskers[2] = VectorFromAngleDegrees(whiskerAngleR1) * whiskerLengthR1;
        whiskers[3] = VectorFromAngleDegrees(whiskerAngleR2) * whiskerLengthR2;




    }

    //Updates Movement
    void Update(float deltaTime)
    {
        m_fish->rotation = AngleFromVector(Normalize(m_fish->velo));
        UpdateWhiskers();







        float MagOfVelo = Length(m_fish->velo);
        if (MagOfVelo > m_maxSpeed)
        {
            m_fish->velo = m_fish->velo * (m_maxSpeed / MagOfVelo);
        };
        m_fish->pos = m_fish->pos + (m_fish->velo * deltaTime) + ((m_fish->accel * 0.5f) * deltaTime * deltaTime);
        m_fish->velo = m_fish->velo + m_fish->accel * deltaTime;
        m_fish->pos = WrapAroundScreen(m_fish->pos);
        m_fish->accel = {};

        //  m_fish->dir = RotateTowards(m_fish->dir, Normalize(m_fish->velo), m_fish->angularSpeed * deltaTime);
    }


    //Returns Acceleration Vector Towards obstacle
    Vector2 Seek(Vector2 const  targetPosition, float deltaTIme)
    {
        Vector2 deltaAccel = Normalize(targetPosition - m_fish->pos) * m_maxSpeed - m_fish->velo;

        m_fish->rotation = AngleFromVector(targetPosition - m_fish->pos);
        //  m_fish->dir = VectorFromAngleDegrees(m_fish->rotation);
        m_fish->accel = deltaAccel;
        return deltaAccel;
    }


    Vector2 Flee(float deltaTime, Vector2 targetPosition)
    {
        Vector2 deltaAccel = (Normalize(targetPosition - m_fish->pos) * m_maxSpeed - m_fish->velo) - 1;
        return deltaAccel;
    }

    void Draw()
    {
        Vector2 veloNorm = Normalize(m_fish->velo);

        DrawCircleV(m_fish->pos, circleRadius, BLACK);
        // DrawLineV(m_fish->pos, m_fish->pos + veloNorm * 100, RED);
        for (int i = 0; i < whiskerCount; i++)
        {
            DrawLineV(m_fish->pos, m_fish->pos + whiskers[i], (detection[i]) ? RED : GREEN);

        }
    }

private:
    float m_maxSpeed; // 350 Px/s 
    float m_maxAacceleration; // 50 Px/s /s
    float whiskerLengthL1;
    float whiskerLengthL2;
    float whiskerLengthR1;
    float whiskerLengthR2;
    RigidBody* m_fish;

    float circleRadius = 40;


    float whiskerAngleL1;
    float whiskerAngleL2;
    float whiskerAngleR1;
    float whiskerAngleR2;

    int whiskerCount = 4;

    bool* detection;
    Vector2* whiskers;

    Vector2 whiskerLeft1;
    Vector2 whiskerLeft2;
    Vector2 whiskerRight1;
    Vector2 whiskerRight2;
};


