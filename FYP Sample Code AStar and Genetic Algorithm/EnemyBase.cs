using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyBase : MonoBehaviour
{
    [SerializeField] private float Health = 10f;
    public Transform target;
    [SerializeField] private float speed = 4;

    public Transform spawnermanager;

    const float minPathUpdateTime = .2f;
    const float pathUpdateMoveThreshold = .5f;
    public float turnSpeed = 100;
    public float turnDst = 1;
    public float stoppingDst = 1;

    public bool isDead;

    [SerializeField] private bool Extrahealth = false;
    [SerializeField] private bool Lessheatlh = false;
    [SerializeField] private bool HigherFireRate = false;
    [SerializeField] private bool LowerFireRate = false;
    [SerializeField] private bool ExtraDistance = false;
    [SerializeField] private bool LessDistance = false;
    [SerializeField] private bool MoreDamage = false;
    [SerializeField] private bool LessDamage = false;
    [SerializeField] private bool MoreSpeed = false;
    [SerializeField] private bool LessSpeed = false;

    private  List<Genes> genesSelected = new List<Genes>();
    private List<Genes> MyGenesList = new List<Genes>();
    private Genes pick = null;

    Path path;

    private int selected = 0;
    void Start()
    {
        isDead = false;
        target = GameObject.FindGameObjectWithTag("Player").transform;
        spawnermanager = GameObject.FindGameObjectWithTag("spawnmanager").transform;

        MyGenesList.AddRange(spawnermanager.GetComponent<genepool>().GetGenesList());

        //while (selected <= 2)
        //{
            GetGenes();
        GetGenes();
        GetGenes();
        Debug.Log(gameObject + " " + selected);
        //}
        StartCoroutine(UpdatePath());
    }


    // TODO:----- Rework this logic as more then three are being picked and i dunno why
    public void GetGenes()
    {

        pick = MyGenesList[Random.Range(0, MyGenesList.Count - 1)];
        for(int i = 0; i < MyGenesList.Count; i++)
        {
            if(MyGenesList[i].name == pick.name)
            {
                MyGenesList.RemoveAt(i);
            }
        }
        
        genesSelected.Add(pick);
        selected++;

        //pick = spawnermanager.GetComponent<genepool>().GetGenes();

        //if (genesSelected.Count == 0 && selected < 3)
        //{
        //    genesSelected.Add(pick);
        //    selected++;

        //    Debug.Log(gameObject + " " + pick.name);
        //}

        //if (genesSelected.Count > 0) { 

        //    for (int i = 0; i<genesSelected.Count; i++)
        //    {
        //        if (pick.name == genesSelected[i].name )
        //        {
        //            //GetGenes();
        //            break;
        //        }
        //        else
        //        {
        //            genesSelected.Add(pick);
        //            selected++;
        //            Debug.Log(gameObject + pick.name);
        //        }
        //    }
        //}





        for (int i = 0; i < genesSelected.Count; i++)
        {
            if (genesSelected[i].name == "ExtraHealth")
            {
                Extrahealth = true;
                Health += genesSelected[i].value;

            }
            if (genesSelected[i].name == "LessHealth")
            {
                Lessheatlh = true;
                Health += genesSelected[i].value;
                if (Health < 0f)
                {
                    Health = 1f;
                }
            }
            if (genesSelected[i].name == "HigherFirerate")
            {
                HigherFireRate = true;
                gameObject.GetComponent<EnemyShoot>().RechargeFireRate += genesSelected[i].value;
                if (gameObject.GetComponent<EnemyShoot>().RechargeFireRate <= 0f)
                {
                    gameObject.GetComponent<EnemyShoot>().RechargeFireRate = 1f;
                }
            }
            if (genesSelected[i].name == "LowerFirerate")
            {
                LowerFireRate = true;
                gameObject.GetComponent<EnemyShoot>().RechargeFireRate += genesSelected[i].value;
                if (gameObject.GetComponent<EnemyShoot>().RechargeFireRate >= 6f)
                {
                    gameObject.GetComponent<EnemyShoot>().RechargeFireRate = 6f;
                }

            }
            if (genesSelected[i].name == "ExtraDamage")
            {
                MoreDamage = true;
                gameObject.GetComponent<EnemyShoot>().projectile.GetComponent<Bulletscore>().SetDamage(genesSelected[i].value);
            }
            if (genesSelected[i].name == "LessDamage")
            {
                LessDamage = true;
                gameObject.GetComponent<EnemyShoot>().projectile.GetComponent<Bulletscore>().SetDamage(genesSelected[i].value);
                if (gameObject.GetComponent<EnemyShoot>().projectile.GetComponent<Bulletscore>().GetDamage() < 0)
                {
                    gameObject.GetComponent<EnemyShoot>().projectile.GetComponent<Bulletscore>().SetDamage(1f);
                }
            }
            if (genesSelected[i].name == "ExtraDistance")
            {
                ExtraDistance = true;
                gameObject.GetComponent<EnemyShoot>().range += genesSelected[i].value;

            }
            if (genesSelected[i].name == "LessDistance")
            {
                LessDistance = true;
                gameObject.GetComponent<EnemyShoot>().range += genesSelected[i].value;
                if (gameObject.GetComponent<EnemyShoot>().range < 3f)
                {
                    gameObject.GetComponent<EnemyShoot>().range = 3f;
                }
            }
            if (genesSelected[i].name == "ExtraSpeed")
            {
                MoreSpeed = true;
                speed += genesSelected[i].value;
                if (speed >= 15f)
                {
                    gameObject.GetComponent<EnemyShoot>().range = 15f;
                }
            }
            if (genesSelected[i].name == "LessSpeed")
            {
                LessSpeed = true;
                speed += genesSelected[i].value;
                if (speed <= 0f)
                {
                    gameObject.GetComponent<EnemyShoot>().range = 1f;
                }
            }
        }

    }

    public List<Genes> GetGenesList()
    {
        return genesSelected;
    }

    public void OnPathFound(Vector3[] waypoints, bool pathSuccessful)
    {
        if (pathSuccessful)
        {
            path = new Path(waypoints, transform.position, turnDst, stoppingDst);

            StopCoroutine("FollowPath");
            StartCoroutine("FollowPath");
        }
    }

    IEnumerator UpdatePath()
    {
        // needs to change target here 

        if (Time.timeSinceLevelLoad < .3f)
        {
            yield return new WaitForSeconds(.3f);
        }
        PathReqManager.RequestPath(new PathRequest(transform.position, target.position, OnPathFound));

        float sqrMoveThreshold = pathUpdateMoveThreshold * pathUpdateMoveThreshold;
        Vector3 targetPosOld = target.position;

        while (true)
        {
            yield return new WaitForSeconds(minPathUpdateTime);
            //print(((target.position - targetPosOld).sqrMagnitude) + "    " + sqrMoveThreshold);
            if ((target.position - targetPosOld).sqrMagnitude > sqrMoveThreshold)
            {
                PathReqManager.RequestPath(new PathRequest(transform.position, target.position, OnPathFound));
                targetPosOld = target.position;
            }
        }
    }

    IEnumerator FollowPath()
    {

        bool followingPath = true;
        int pathIndex = 0;
        transform.LookAt(path.lookPoints[0]);
        //transform.LookAt(transform.forward);

        float speedPercent = 1;

        while (followingPath)
        {
            Vector2 pos2D = new Vector2(transform.position.x, transform.position.z);
            while (path.turnBoundaries[pathIndex].HasCrossedLine(pos2D))
            {
                if (pathIndex == path.finishLineIndex)
                {
                    followingPath = false;
                    break;
                }
                else
                {
                    pathIndex++;
                }
            }

            if (followingPath)
            {

                if (pathIndex >= path.slowDownIndex && stoppingDst > 0)
                {
                    speedPercent = Mathf.Clamp01(path.turnBoundaries[path.finishLineIndex].DistanceFromPoint(pos2D) / stoppingDst);
                    if (speedPercent < 0.01f)
                    {
                        followingPath = false;
                    }
                }

                Quaternion targetRotation = Quaternion.LookRotation(path.lookPoints[pathIndex] - transform.position);
                transform.rotation = Quaternion.Lerp(transform.rotation, targetRotation, Time.deltaTime * turnSpeed);
                transform.Translate(Vector3.forward * Time.deltaTime * speed * speedPercent, Space.Self);
            }

            yield return null;

        }
        
    }

    public void OnDrawGizmos()
    {
        if (path != null)
        {
            path.DrawWithGizmos();
        }
    }


    public void TakeDamage(float damage)
    {
        Health -= damage;

        if (Health <= 0 && !isDead)
        {
            isDead = true;
            Debug.Log("DEAD");
            spawnermanager.GetComponent<Spawner>().DestroyEnemies();
            gameObject.GetComponent<MeshRenderer>().enabled = false;
            gameObject.GetComponent<CapsuleCollider>().enabled = false;
            //Destroy(gameObject);    
        }
    }

}