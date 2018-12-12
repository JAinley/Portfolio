using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyShoot : MonoBehaviour {

    public Transform player;
    public float range = 10.0f;
    public float bulletImpulse = 20.0f;
    public float myrange = 10000;
    private float rand;
    private float score;
    public bool onRange = false;
    public float firerate;
    public float RechargeFireRate = 2f;
    private bool canShoot;
    public Rigidbody projectile;
    
    // Use this for initialization
    void Start() {
        clearScore();
        firerate = RechargeFireRate;
        player = GameObject.FindGameObjectWithTag("Player").transform;
        rand = Random.Range(1.0f, 2.0f);
        Debug.Log(projectile.GetComponent<Bulletscore>().GetDamage());
    }
  

    void Shoot()
    {
        Rigidbody bullet = (Rigidbody)Instantiate(projectile, transform.position + transform.forward, transform.rotation);
        bullet.AddForce(transform.forward * bulletImpulse, ForceMode.Impulse);
        
    }

    void Update()
    {
        if (gameObject.GetComponent<EnemyBase>().isDead == false)
        {
            transform.LookAt(player.transform);
            RaycastHit hit;
            // here you can set a distance you need the AI to be from the player to shoot,, another for the traits list??
            onRange = Vector3.Distance(transform.position, player.position) < range;
            Vector3 directionToPlayer = player.position - transform.position;
            Debug.DrawRay(transform.position, transform.forward, Color.red);

            if (Physics.Raycast(transform.position, directionToPlayer, out hit, 100))
            {
                if (hit.transform.gameObject == player.gameObject)
                {
                    if (onRange)
                    {
                        if (firerate > 0)
                        {
                            firerate -= Time.deltaTime;
                            return;
                        }
                        Shoot();
                        firerate = RechargeFireRate;
                    }
                }

            }
            transform.GetComponent<EnemyBase>().target = player;
        }
    }

    public void UpdateScore(float score_)
    {
        score = score + score_;
    }

    public void clearScore()
    {
        score = 0;
    }

    public float GetScore()
    {
        return score;
    }
}
