using System;
using System.Collections;
using System.Collections.Generic;

using System.Runtime.InteropServices;
using UnityEngine;

public class pluginConnector : MonoBehaviour
{
    [SerializeField]
    private int numberOfPlayers;
    [SerializeField]
    private int numberOfBaseStations;
    [SerializeField]
    [Range(0.0f,0.5f)]
    private float positionUpdateInterval;

    private const string dllName = "libtracking";

    private int size;

    [DllImport(dllName)]
    private static extern void startTracking(int numberOfPlayers, int numberOfBaseStations);
    [DllImport(dllName)]
    private static extern void stopTracking();
    [DllImport(dllName)]
    private static extern void updatePositions(int size, [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 0)] float[] array);
    [DllImport(dllName)]
    private static extern void pointerTest(int size, [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 0)] double[] array);
    [DllImport(dllName)]
    private static extern int getSize();

    // Start is called before the first frame update

    void Awake()
    {
        startTracking(numberOfPlayers,numberOfBaseStations);
    }

    private void OnDisable()
    {
        stopTracking();
    }


    void Start()
    {
        size = getSize();
        StartCoroutine("DoCheck");
    }

    // Update is called once per frame
    void Update()
    {
        

        
    }


    IEnumerator DoCheck()
    {
        for(; ; )
        {
            float[] arr = new float[size];
            updatePositions(size,arr);
            Debug.Log(arr[0] + "," + arr[1] + "," + arr[2]);
            yield return new WaitForSeconds(positionUpdateInterval);
        }
    }

    
}
