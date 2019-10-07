/* libacmequeue
 *
 * Copyright (C) 2019 - Acme Amalgmated Widgets
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

 #define QUEUE_PATH "/tmp"

class AcmeQueue {
  private:
    char dirName[255];
    char* queueName;
    char* queuePath;
    bool Debug;
    void createDir(const char *qp, const char *qn);
    bool getDebug();
  public:
    AcmeQueue(const char *qn); 
    AcmeQueue(const char *qp, const char *qn);
    int Push(const char *s);
    bool Pop(char *s);
    void List();
    void setDebug(bool d);
};
