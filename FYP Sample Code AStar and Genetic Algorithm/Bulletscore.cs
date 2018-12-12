using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bulletscore : MonoBehaviour {

    public GameObject EnemyShooter;
    private float damage = 5;

	// Use this for initialization
	void Start () {
        damage = 5;
	}
	
	// Update is called once per frame
	void Update () {

    }

    public void OnCollisionEnter(Collision player)
    {
        if (player.collider.tag == "Player")
        {
            
            //Debug.Log("bullet hit");
            EnemyShooter.GetComponent<EnemyShoot>().UpdateScore(damage);
            Destroy(gameObject);
        }
    }

    public void SetDamage(float NewDamage)
    {
        damage += NewDamage;
    }
    public float GetDamage()
    {
        return damage;
    }
}
