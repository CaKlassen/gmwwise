{
    "id": "70848441-40d1-42b2-8008-392246d5b39b",
    "modelName": "GMExtension",
    "mvc": "1.0",
    "name": "GMWwise",
    "IncludedResources": [
        
    ],
    "androidPermissions": [
        
    ],
    "androidProps": false,
    "androidactivityinject": "",
    "androidclassname": "",
    "androidinject": "",
    "androidmanifestinject": "",
    "androidsourcedir": "",
    "author": "",
    "classname": "",
    "date": "2017-52-21 01:04:23",
    "description": "",
    "extensionName": "",
    "files": [
        {
            "id": "8806515b-e502-42ba-9e41-996815c53aef",
            "modelName": "GMExtensionFile",
            "mvc": "1.0",
            "ConfigOptions": [
                {
                    "Key": "default",
                    "Value": 609259586
                }
            ],
            "ProxyFiles": [
                {
                    "id": "0c6ad6a4-f0b4-4e50-9387-ff40e9959599",
                    "modelName": "GMProxyFile",
                    "mvc": "1.0",
                    "TargetMask": 6,
                    "proxyName": "GMWwise_profile.dll"
                },
                {
                    "id": "eaafb7fa-485f-4643-9355-9fad7e4e0a96",
                    "modelName": "GMProxyFile",
                    "mvc": "1.0",
                    "TargetMask": 1,
                    "proxyName": "libGMWwise_profile.dylib"
                }
            ],
            "constants": [
                
            ],
            "filename": "GMWwise_profile.dll",
            "final": "",
            "functions": [
                {
                    "id": "f29f631b-f615-4787-bd47-554b584def08",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        1
                    ],
                    "externalName": "GMWSetBasePath",
                    "help": "gmwSetBasePath(path)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwSetBasePath",
                    "returnType": 2
                },
                {
                    "id": "a4d138ea-18c9-4094-8ce3-d50f17f3a6d9",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        1
                    ],
                    "externalName": "GMWLoadBank",
                    "help": "gmwLoadBank(bankName)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwLoadBank",
                    "returnType": 2
                },
                {
                    "id": "aabffe70-1b2b-4643-ab25-0bc8a4fa96de",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "GMWUnloadBank",
                    "help": "gmwUnloadBank(bankID)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwUnloadBank",
                    "returnType": 2
                },
                {
                    "id": "39828ef2-c1bd-4a7d-95a4-0694bc806149",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 0,
                    "args": [
                        
                    ],
                    "externalName": "GMWInit",
                    "help": "gmwInit()",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwInit",
                    "returnType": 2
                },
                {
                    "id": "b80c1652-360a-4d2d-8d7e-a2ee1b3cd447",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 0,
                    "args": [
                        
                    ],
                    "externalName": "GMWShutdown",
                    "help": "gmStop()",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwStop",
                    "returnType": 2
                },
                {
                    "id": "500960a9-8568-4093-8934-e267dae042b0",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": -1,
                    "args": [
                        
                    ],
                    "externalName": "GMWProcessAudio",
                    "help": "gmwProcess()",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwProcess",
                    "returnType": 2
                },
                {
                    "id": "5b052123-cfbb-4d49-83d6-90b170a15a1f",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "GMWSetState",
                    "help": "gmwSetState(stateGroup,state)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwSetState",
                    "returnType": 2
                },
                {
                    "id": "d35b4426-8493-4c63-849d-fb49920bf08f",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "GMWRegisterGroupGameObj",
                    "help": "gmwRegisterGroup(groupID)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwRegisterGroup",
                    "returnType": 2
                },
                {
                    "id": "1be66de4-aab5-490c-889b-bf4b265bce32",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "GMWUnregisterGroupGameObj",
                    "help": "gmwUnregisterGroup(groupID)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwUnregisterGroup",
                    "returnType": 2
                },
                {
                    "id": "4d0654b2-84e7-495e-a12e-1508a0bb84bb",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 3,
                    "args": [
                        2,
                        2,
                        1
                    ],
                    "externalName": "GMWRegisterGameObj",
                    "help": "gmwRegisterObject(objectID,groupID,objectName)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwRegisterObject",
                    "returnType": 2
                },
                {
                    "id": "c3c743fd-6bc8-4f1a-b616-e69219bd42f4",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "GMWUnregisterGameObj",
                    "help": "gmwUnregisterObject(objectID,groupID)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwUnregisterObject",
                    "returnType": 2
                },
                {
                    "id": "14338f5b-b121-4bdf-8b4b-fb97e7ca2e67",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 5,
                    "args": [
                        2,
                        2,
                        2,
                        2,
                        2
                    ],
                    "externalName": "GMWSet2DPosition",
                    "help": "gmwSet2DPosition(objectID,xPos,yPos,xOr,yOr)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwSet2DPosition",
                    "returnType": 2
                },
                {
                    "id": "037b955c-2d5d-4ea9-9494-84608a8b429e",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 7,
                    "args": [
                        2,
                        2,
                        2,
                        2,
                        2,
                        2,
                        2
                    ],
                    "externalName": "GMWSet3DPosition",
                    "help": "gmwSet3DPosition(objectID,xPos,yPos,zPos,xOr,yOr,zOr)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwSet3DPosition",
                    "returnType": 2
                },
                {
                    "id": "770ce52e-71ea-40b3-8ed1-a4d6574b344f",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "GMWPostEvent",
                    "help": "gmwPostEvent(eventID,objectID)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwPostEvent",
                    "returnType": 2
                },
                {
                    "id": "9833fd2e-b67c-4f9c-959c-f74c470e7d37",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "GMWPostTrigger",
                    "help": "gmwPostTrigger(triggerID,objectID)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwPostTrigger",
                    "returnType": 2
                },
                {
                    "id": "1bd6ea7b-2620-4c65-b3ff-1024e7d05f59",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 1,
                    "args": [
                        2
                    ],
                    "externalName": "GMWStopAll",
                    "help": "gmwStopAll(objectID)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwStopAll",
                    "returnType": 2
                },
                {
                    "id": "0579fddb-a515-4131-9a53-f74b8ff0d849",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 3,
                    "args": [
                        2,
                        2,
                        2
                    ],
                    "externalName": "GMWSetRTPCValue",
                    "help": "gmwSetParameter(rtpcID,rtpcValue,objectID)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwSetParameter",
                    "returnType": 2
                },
                {
                    "id": "68bd2370-aa51-453f-bdbf-c540f32ff9ec",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "GMWSetGlobalRTPCValue",
                    "help": "gmwSetGlobalParameter(rtpcID,rtpcValue)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwSetGlobalParameter",
                    "returnType": 2
                },
                {
                    "id": "fdfe4444-8703-4f7c-891c-dbf325cbb73d",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "GMWGetRTPCValue",
                    "help": "gmwGetParameter(rtpcID,objectID)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwGetParameter",
                    "returnType": 2
                },
                {
                    "id": "6bef6002-0ba9-4289-b899-78c873cfc9c3",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 3,
                    "args": [
                        2,
                        2,
                        2
                    ],
                    "externalName": "GMWSetSwitch",
                    "help": "gmwSetSwitch(switchGroup,switchID,objectID)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwSetSwitch",
                    "returnType": 2
                },
                {
                    "id": "4574dad6-7202-48f3-bf30-c9d77fa59b30",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 4,
                    "args": [
                        2,
                        2,
                        2,
                        2
                    ],
                    "externalName": "GMWSet2DListenerPosition",
                    "help": "gmwSet2DListenerPosition(xPos,yPos,xOr,yOr)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwSet2DListenerPosition",
                    "returnType": 2
                },
                {
                    "id": "f7bbc6c8-5664-4e04-a372-6b9e7865044d",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 6,
                    "args": [
                        2,
                        2,
                        2,
                        2,
                        2,
                        2
                    ],
                    "externalName": "GMWSet3DListenerPosition",
                    "help": "gmwSet3DListenerPosition(xPos,yPos,zPos,xOr,yOr,zOr)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwSet3DListenerPosition",
                    "returnType": 2
                },
                {
                    "id": "13434a3f-ce77-4704-9d96-9c664727234a",
                    "modelName": "GMExtensionFunction",
                    "mvc": "1.0",
                    "argCount": 2,
                    "args": [
                        2,
                        2
                    ],
                    "externalName": "GMWSetActiveListeners",
                    "help": "gmwSetActiveListeners(objectID,listenerBitmask)",
                    "hidden": false,
                    "kind": 12,
                    "name": "gmwSetActiveListeners",
                    "returnType": 2
                }
            ],
            "init": "",
            "kind": 1,
            "maskTarget": 0,
            "order": [
                "f29f631b-f615-4787-bd47-554b584def08",
                "a4d138ea-18c9-4094-8ce3-d50f17f3a6d9",
                "aabffe70-1b2b-4643-ab25-0bc8a4fa96de",
                "39828ef2-c1bd-4a7d-95a4-0694bc806149",
                "b80c1652-360a-4d2d-8d7e-a2ee1b3cd447",
                "500960a9-8568-4093-8934-e267dae042b0",
                "5b052123-cfbb-4d49-83d6-90b170a15a1f",
                "d35b4426-8493-4c63-849d-fb49920bf08f",
                "1be66de4-aab5-490c-889b-bf4b265bce32",
                "4d0654b2-84e7-495e-a12e-1508a0bb84bb",
                "c3c743fd-6bc8-4f1a-b616-e69219bd42f4",
                "14338f5b-b121-4bdf-8b4b-fb97e7ca2e67",
                "037b955c-2d5d-4ea9-9494-84608a8b429e",
                "770ce52e-71ea-40b3-8ed1-a4d6574b344f",
                "9833fd2e-b67c-4f9c-959c-f74c470e7d37",
                "1bd6ea7b-2620-4c65-b3ff-1024e7d05f59",
                "0579fddb-a515-4131-9a53-f74b8ff0d849",
                "68bd2370-aa51-453f-bdbf-c540f32ff9ec",
                "fdfe4444-8703-4f7c-891c-dbf325cbb73d",
                "6bef6002-0ba9-4289-b899-78c873cfc9c3",
                "4574dad6-7202-48f3-bf30-c9d77fa59b30",
                "f7bbc6c8-5664-4e04-a372-6b9e7865044d",
                "13434a3f-ce77-4704-9d96-9c664727234a"
            ],
            "origname": "extensions\\GMWwise_profile.dll",
            "uncompress": false
        }
    ],
    "gradleinject": "",
    "helpfile": "",
    "installdir": "",
    "iosProps": false,
    "iosSystemFrameworkEntries": [
        
    ],
    "iosThirdPartyFrameworkEntries": [
        
    ],
    "iosplistinject": "",
    "license": "Free to use, also for commercial games.",
    "maccompilerflags": "",
    "maclinkerflags": "",
    "macsourcedir": "",
    "packageID": "",
    "productID": "",
    "sourcedir": "",
    "version": "1.4.0"
}