using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class doublescreenCameramanager : MonoBehaviour
{
    Vector3 shiftingCamera1 = new Vector3(50,0,29.21f);
    Vector3 shiftingCamera2 = new Vector3(51, 0, 72);


    public Color backgroundColor;
    /// <summary>
    /// This script just open the two screens on the same allication
    /// </summary>
    void Awake()
    {
        //NB: screen indexes start from 1
        for (int i = 0; i < GameObject.FindObjectsOfType<Camera>().Length; i++)
        {
            if (i < Display.displays.Length)
            {
                Display.displays[i].Activate();
            }
        }

        transform.GetChild(0).transform.localPosition = shiftingCamera1;
        transform.GetChild(1).transform.localPosition = shiftingCamera2;

        transform.GetChild(0).GetComponent<Camera>().backgroundColor = backgroundColor;
        transform.GetChild(1).GetComponent<Camera>().backgroundColor = backgroundColor;
    }

}
