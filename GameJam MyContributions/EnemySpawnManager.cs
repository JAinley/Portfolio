using UnityEngine;

public class EnemySpawnManager : MonoBehaviour
{
    public GameObject enemy;                // The enemy prefab to be spawned.
    public GameObject tankEnemy;
    public float spawnTime;            // How long between each spawn.
    public Transform[] spawnPoints;         // An array of the spawn points this enemy can spawn from.
    public int numberOfZombies;
    public int maxNumberOfZombies = 100;
    private float gameStartTimer;
    void Start()
    {
        // Call the Spawn function after a delay of the spawnTime and then continue to call after the same amount of time.
        Invoke("SpawnZombie", spawnTime);
    }

    void Update()
    {
        gameStartTimer += 1f * Time.deltaTime;

        if (gameStartTimer <= 10f)
            spawnTime = 0.1f;
        else
            spawnTime = 3f;

        Invoke("SpawnZombie", spawnTime);


    }

    void SpawnZombie()
    {

        if (numberOfZombies == maxNumberOfZombies)
        {
            return;
        }
        else
        {
            
            // Find a random index between zero and one less than the number of spawn points.
            int spawnPointIndex = Random.Range(0, spawnPoints.Length);

            // Create an instance of the enemy prefab at the randomly selected spawn point's position and rotation.
            Instantiate(enemy, spawnPoints[spawnPointIndex].position, spawnPoints[spawnPointIndex].rotation);
            //Debug.Log("Zombie Spawned");
            numberOfZombies += 1;
        }
    }

}