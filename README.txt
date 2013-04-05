                                                                     
                                                                     
                                                                     
                                             
-----------------------------------------------------------------
This module creates Achievement Entity user interface(UI) for creating entities 
using entity module.

bundles can be created with this UI. 

Current features and design
---------------------------

* The module is aimed to provide a simple, but extensible solution providing a 
  similar entity type for comments, user profile,etc.
* Achievement Entity module creates user interface for creating bundle through 
  this.
* Permission can be set for bundle.
* All content of all bundles can be shown on Openbadging Configuration content 
  tab.



Installation
-------------

* Copy the whole "openbadging" directory to your modules
  directory - "sites/all/modules"
* Enable the module and add bundles at - "admin/structure/achievement".
* Set your desired bundle wise permissions at - "admin/people/permissions".


Usage
------
   
 * Go to "/admin/structure/Achievement"(structure >> Openbadging Configurations)
   and add bundles.
 * For add any content for these bundles go to achievement/add.
 * All content saved in content tab at admin/structure/achievement/content.

Permissions available for each bundle
-------------------------------------
* View Bundle achievement
* Create Bundle achievement
* Edit any Bundle achievement
* Edit own Bundle achievement
* Delete any Bundle achievement
* Delete own Bundle achievement

