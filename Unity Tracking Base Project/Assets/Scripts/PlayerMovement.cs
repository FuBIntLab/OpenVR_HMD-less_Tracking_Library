using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    // Start is called before the first frame update
    public Quaternion q;
    public bool manual;
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void setPosition(Vector3 pos)
    {
        float size = Mathf.Clamp(pos.y, 0, 4);
        transform.localScale = new Vector3(pos.y, pos.y, pos.y);
        transform.position = pos;
    }

    public void setRotation(Quaternion quat)
    {
        //Vector3 eulerAngles =  quat.eulerAngles;
        //Quaternion newQuat = Quaternion.Euler(eulerAngles.y, eulerAngles.z, -eulerAngles.x);
        transform.localRotation = quat;
    }
}
