using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class genepool : MonoBehaviour {
   

    public List<Genes> genes = new List<Genes>();

    [Range(1f, 2f)]
    public float mutatorValue;

    //public Text Gene1;
    //public Text Gene2;
    //public Text Gene3;
    //public Text Gene4;
    //public Text Gene5;
    //public Text Gene6;
    //public Text Gene7;
    //public Text Gene8;
    //public Text Gene9;
    //public Text Gene10;


    // Use this for initialization
    void Start () {
        RemoveGenes();
        AddGeneList();
    }
	
	// Update is called once per frame
	void Update () {

       // //if (genes[0] != null)
       //// {
       //     Gene1.text = "1." + genes[0].name;
       // //}
       // //if (genes[1] != null)
       // //{
       //     Gene2.text = "2." + genes[1].name;
       // //}
       // //if (genes[2] != null)
       // //{
       //     Gene3.text = "3." + genes[2].name;
       // //}
       // //if (genes[3] != null)
       // //{
       //     Gene4.text = "4." + genes[3].name;
       // //}
       // //if (genes[4] != null)
       // //{
       //     Gene5.text = "5." + genes[4].name;
       // //}
       // //if (genes[5] != null)
       // //{
       //     Gene6.text = "6." + genes[5].name;
       // //}
       // //if (genes[6] != null)
       // //{
       //     Gene7.text = "7." + genes[6].name;
       // //}
       // //if (genes[7] != null)
       // //{
       //     Gene8.text = "8." + genes[7].name;
       // //}
       // //if (genes[8] != null)
       // //{
       //     Gene9.text = "9." + genes[8].name;
       // //}
       // //if (genes[9] != null)
       // //{
       //     Gene10.text = "10." + genes[9].name;
       // //}

    }

    // cant have the partner gene such as cant have extra health and less health
    public Genes GetGenes()
    {
        Genes pick = genes[Random.Range(0, genes.Count - 1)];

        return pick;
    }

    public void AddGeneList()
    {
        RemoveGenes();
        genes.Add(new Genes() { name = "ExtraHealth", value = 5f });
        genes.Add(new Genes() { name = "LessHealth", value = -3f });
        genes.Add(new Genes() { name = "HigherFirerate", value = -3f });
        genes.Add(new Genes() { name = "LowerFirerate", value = 3f });
        genes.Add(new Genes() { name = "ExtraDamage", value = 3f });
        genes.Add(new Genes() { name = "LessDamage", value = -1f });
        genes.Add(new Genes() { name = "ExtraDistance", value = 5f });
        genes.Add(new Genes() { name = "LessDistance", value = -3f });
        genes.Add(new Genes() { name = "ExtraSpeed", value = 2f });
        genes.Add(new Genes() { name = "LessSpeed", value = -2f });



    }

    public void Mutator()
    {

        Genes pick = genes[Random.Range(0, genes.Count - 1)];

        pick.value *= mutatorValue;

    }

    public void FillGenePool(List<Genes> newGenes)
    {
        genes.AddRange(newGenes);
    }
    public List<Genes> GetGenesList()
    {
        return genes;
    }

    public void RemoveGenes()
    {
        genes.Clear();

        Debug.Log("Cleared list");
    }
}
