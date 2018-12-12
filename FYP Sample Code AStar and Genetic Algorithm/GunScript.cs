using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GunScript : MonoBehaviour {

    public float damage = 5f;
    public float range = 100f;
    public Camera camera;
    public ParticleSystem muzzleflash;

   
	// Update is called once per frame
	void Update () {
		if (Input.GetButtonDown("Fire1"))
        {
            Shoot();
        }
	}

    void Shoot()
    {
        muzzleflash.Play();
        RaycastHit hit;
        if(Physics.Raycast(camera.transform.position, camera.transform.forward, out hit, range))
        {
            if(hit.transform.GetComponent<EnemyBase>())
            {
                hit.transform.GetComponent<EnemyBase>().TakeDamage(damage);
            }

            //Debug.Log("HIT");
        }
    }
}
