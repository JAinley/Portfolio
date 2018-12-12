using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour {

    public GameObject EnemyA;
    public GameObject EnemyB;
    public GameObject EnemyC;
    public GameObject EnemyD;
    public GameObject EnemyE;

    public float spawnTime = 3f;
    public float roundNumber = 0;
    public Transform spawnPointA;
    public Transform spawnPointB;
    public Transform spawnPointC;
    public Transform spawnPointD;
    public Transform spawnPointE;

    public float round;
    public bool roundInProgress;
    List<GameObject> Enemies = new List<GameObject>();

    // Use this for initialization
    void Start () {
     
	}


    // score system needs to compare to see who comes out on top and then the top two need to donate their genes to the genepool
  

    void Spawn()
    {

        Enemies.Clear();

        round ++;
        roundInProgress = true;


        Enemies.Add(Instantiate(EnemyA, spawnPointA.position, spawnPointA.rotation));
        Enemies.Add(Instantiate(EnemyB, spawnPointB.position, spawnPointB.rotation));
        Enemies.Add(Instantiate(EnemyC, spawnPointC.position, spawnPointC.rotation));
        Enemies.Add(Instantiate(EnemyD, spawnPointD.position, spawnPointD.rotation));
        Enemies.Add(Instantiate(EnemyE, spawnPointE.position, spawnPointE.rotation));

        EnemyA.GetComponent<EnemyShoot>().clearScore();
        EnemyB.GetComponent<EnemyShoot>().clearScore();
        EnemyC.GetComponent<EnemyShoot>().clearScore();
        EnemyD.GetComponent<EnemyShoot>().clearScore();
        EnemyE.GetComponent<EnemyShoot>().clearScore();

        
    }


    void Update()
    {

        if (!roundInProgress && Input.GetButtonDown("Fire2"))
        {
            Spawn();
            
        }

        if (roundNumber >= 5)
        {
            Enemies.Sort((x, y) => x.gameObject.GetComponent<EnemyShoot>().GetScore().CompareTo(y.gameObject.GetComponent<EnemyShoot>().GetScore()));

            gameObject.GetComponent<genepool>().RemoveGenes();

            gameObject.GetComponent<genepool>().FillGenePool(Enemies[0].GetComponent<EnemyBase>().GetGenesList());
            gameObject.GetComponent<genepool>().FillGenePool(Enemies[1].GetComponent<EnemyBase>().GetGenesList());
            gameObject.GetComponent<genepool>().Mutator();
            roundInProgress = false;
            roundNumber = 0;
            Enemies.Clear();
        }
        
    }

    public void DestroyEnemies()
    {
        roundNumber++;
        Debug.Log(roundNumber);
    }

}
