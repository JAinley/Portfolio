using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Scores : MonoBehaviour {

    public GameObject EnemyA;
    public GameObject EnemyB;
    public GameObject EnemyC;
    public GameObject EnemyD;
    public GameObject EnemyE;
    public GameObject Manager;

    public Text scoreA;
    public Text scoreB;
    public Text scoreC;
    public Text scoreD;
    public Text scoreE;
    public Text Round;


    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        scoreA.text = "EnemyA Score: " + EnemyA.GetComponent<EnemyShoot>().GetScore();
        scoreB.text = "EnemyB Score: " + EnemyB.GetComponent<EnemyShoot>().GetScore();
        scoreC.text = "EnemyC Score: " + EnemyC.GetComponent<EnemyShoot>().GetScore();
        scoreD.text = "EnemyD Score: " + EnemyD.GetComponent<EnemyShoot>().GetScore();
        scoreE.text = "EnemyE Score: " + EnemyE.GetComponent<EnemyShoot>().GetScore();

        //Round.text = "Round: " + Manager.GetComponent<Spawner>().round;
    }
}
