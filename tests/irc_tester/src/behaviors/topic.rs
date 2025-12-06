use crate::client::Client;
use anyhow::Result;


   // TopicRpl,
    // TopicNoPriv,
    // TopicNoChanModes,

pub async fn topic_need_more_params(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("{}_topic_params", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}\r\n", nick), 0)
        .await?;
    client
        .send(
            &format!(
                "USER {}_topic_more_params 0 * :topic_need_more_params\r\n",
                nick
            ),
            0,
        )
        .await?;

    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }

    client.send("TOPIC \r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :Not enough parameters") {
            return Err(anyhow::anyhow!("Err_NEEDMOREPARAMS missing | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}

pub async fn topic_not_on_chan(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("{}_topic_not_on_chan", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}\r\n", nick), 0)
        .await?;
    client
        .send(
            &format!(
                "USER {}_topic_more_params 0 * :topic_need_more_params\r\n",
                nick
            ),
            0,
        )
        .await?;

    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }

    client.send("TOPIC #no_mdp_chan\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :You're not on that channel") {
            return Err(anyhow::anyhow!("ERR_NOTONCHAN missing | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}

pub async fn topic_no_topic(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("{}_topic_no_topic", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}\r\n", nick), 0)
        .await?;
    client
        .send(
            &format!(
                "USER {} 0 * :topic_need_more_params\r\n",
                nick
            ),
            0,
        )
        .await?;

    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }

    client.send("JOIN #no_mdp_chan\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" JOIN #no_mdp_chan") {
            return Err(anyhow::anyhow!("Failed to join #no_mdp_chan | received [{line}]"));
        }
    }
    client.send("TOPIC #no_mdp_chan\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :No topic is set") {
            return Err(anyhow::anyhow!("ERR_NOTOPIC missing | received [{line}]"));
        }
    }

    client.shutdown().await?;
    Ok(())
}


